#include "inode.h"
#include <assert.h>

unsigned int current_vol;

void read_inode (unsigned int inumber, struct inode_s* inode) {
	assert(BLOC_SIZE == sizeof(struct inode_s));
	read_bloc(current_vol, inumber, (unsigned char *)inode);
}

void write_inode (unsigned int inumber, const struct inode_s *inode) {
	assert(BLOC_SIZE == sizeof(struct inode_s));
	write_bloc(current_vol, inumber, (unsigned char *)inode);
}

void free_blocs(unsigned int *bloc, unsigned int n) {
	int i;
	for(i=0; i < n ; i++) {
		if(bloc[i]){
			free_bloc(bloc[i]);
		}
	}
}

/* alloue et initialise un bloc et range l'inoeud dedans retourne l'inode correspondant*/
unsigned int create_inode(enum file_type_e type) {
	int i,inumber;
	struct inode_s inode;
	inode.type = type;
	inode.ind_size = 0; /* inode size */
	for(i = 0 ; i < NDIRECT; i++) {
		inode.direct[i] = 0;
	}
	inumber = new_bloc();
	if(inumber == 0) { return 0;} /* volume plein */
	write_inode(inumber,&inode); /*on alloue le bloc pour y ranger l'inoeud */
	return inumber;
}

int delete_inode(unsigned int inumber) {
	struct inode_s inode;
	int i;
	read_inode(inumber,&inode);
	/* ici on libère les directs de l'inode */
	free_blocs(inode.direct,NDIRECT);

	if(inode.indirect) { /* si c'est différent de zéro = il existe */
		unsigned int bloc[NBPB];
		read_blocn(current_vol,inode.indirect,(unsigned char *)bloc,NBPB*sizeof(unsigned));
		free_blocs(bloc,NBPB);
		free_bloc(inode.indirect);
	}
	if(inode.two_indirect) {
		read_blocn(current_vol, inumber, (unsigned char *)inode.two_indirect,NBPB*sizeof(unsigned));
		for(i = 0; i < NBPB; i++) {
			unsigned int tmp[NBPB];
			read_blocn(current_vol, inode.two_indirect, (unsigned char *)tmp,NBPB*sizeof(unsigned));
			free_blocs(tmp, NBPB);
		}
		free_bloc(inode.two_indirect);
		//free_blocs(inode,NBPB);
	}
	free_bloc(inode.two_indirect);

	free_bloc(inumber);
	return inumber;
}


// Recopié depuis le cahier, les noms sont pas forcément les bons
unsigned int vbloc_of_fbloc(unsigned int inumber, unsigned int fbloc,bool_t do_allocate){
	struct inode_s inode;
	unsigned int bloc_index = fbloc;
	read_inode(inumber, &inode);

	//direct
	if (bloc_index < NDIRECTS){
		if (inode.direct[bloc_index] == 0){
			if(do_allocate){
				inode.direct[bloc_index] = initialize_bloc(new_bloc());
				write_inode(inumber,&inode);
			}else{return BLOC_NULL;}
		}
		return inode.direct[bloc_index];
	}
	bloc_index -= NDIRECTS;

	//indirect simple
	if (bloc_index < NBPB){
		// if the indirect entry in the inode is not allocated yet
		if (inode.direct == 0){
			if(do_allocate){
				inode.indirect = initialize_bloc(new_bloc());;
				write_inode(inumber,&inode);
			}else{return BLOC_NULL;}
		}
		
		int indirect[NBPB];	
		read_bloc(current_volume, inode.indirect, (unsigned char *)indirect);
		
		if (indirect[bloc_index] == 0){
			if(do_allocate){
				indirect[bloc_index] = initialize_bloc(new_bloc());;
				write_bloc(current_volume, inode.indirect, (unsigned char*)indirect);
			}else{return BLOC_NULL;}
		}
		return indirect[bloc_index];
	}
	
	bloc_index -= NBPB;
	
	//indirect double
	if(bloc_index < NBPB*NBPB){
		if (inode.blocs_double_indirect == 0){
			if(do_allocate){
				inode.blocs_double_indirect = initialize_bloc(new_bloc());;
				write_inode(inumber,&inode);
			}else{return BLOC_NULL;}
		}	
		int db_indirect_index = bloc_index / NBPB;
		int indirect_index = bloc_index % NBPB; 				
		int db_indirect[NBPB];
		read_bloc(current_volume, inode.blocs_double_indirect, (unsigned char*)db_indirect);
		
		if (db_indirect[db_indirect_index] == 0){
			if(do_allocate){
				db_indirect[db_indirect_index] = initialize_bloc(new_bloc());
				write_bloc(current_volume, inode.blocs_double_indirect, (unsigned char*)db_indirect);
			}else{return BLOC_NULL;}
		}
		
		int indirect[NBPB];	
		read_bloc(current_volume, db_indirect[db_indirect_index], (unsigned char*)indirect);
		
		if (indirect[indirect_index] == 0){
			if(do_allocate){
				//printf("allocate indirect[%d]\n",indirect_index);
				indirect[indirect_index] = initialize_bloc(new_bloc());;
				write_bloc(current_volume, db_indirect[db_indirect_index], (unsigned char*)indirect);
			}else{return BLOC_NULL;}
		}
		return indirect[indirect_index]; 		
	}
	
	fprintf(stderr,"fbloc is too big.\n\tfbloc provided: %d\n\tfbloc max size: %d",fbloc, NDIRECTS+NBPB+NBPB*NBPB);
	return -1;
}
