#include "inode.h"
#include <assert.h>

unsigned int current_vol;

void read_inode (unsigned int inumber, struct inode_s* inode) {
	assert(BLOC_SIZE == sizeof(struct inode_s));
	read_bloc(current_vol, inumber, (unsigned char *)inode);
}

void write_inode (unsigned int inumber, struct inode_s *inode) {
	assert(BLOC_SIZE == sizeof(struct inode_s));
	write_bloc(current_vol, inumber, (unsigned char *)inode);
}

unsigned int create_inode(enum file_type_e type) {
	int i,inumber;
	struct inode_s inode;
	inode.type = type;
	inode.ind_size = 0;
	inode.taille = 0;
	for(i = 0 ; i < n ; i++) {
		inode.inode_direct[i] = 0;
	}
	inumber = new_bloc();
	if(inumber == 0) { return 0;} /* volume plein */
	write_inode(inumber,&inode);
	return inumber;
}

int delete_inode(unsigned int inumber) {
	free_blocs(unsigned int bloc[],unsigned int n);
//	free_blocs(ine.indirect_direct,indirect); whaaat ?
	if(inode.inode_indirect) {
		unsigned bloc[NBPB];
		read_blocn(inode.indirect,bloc,NBPB*sizeof(unsigned));
		free_blocs(bloc,&NBPB);
		free_bloc(inode.indirect);
	}
	if(inode.two_indirect) {
		read_blocn(current_vol, inumber, (unsigned char *)inode.two_indirect);
		for(i = 0; i < NBPB; i++) {
			unsigned int tmp[NBPB];
			read_blocn(current_vol, inode.two_indirect, (unsigned char *)tmp);
			free_blocs(tmp, NBPB);
			free_bloc(inode.two_indirect);
		}
		free_blocs(bloc, NB_BLOCS_BY_BLOC);
	}
	free_bloc(inode.two_indirect);

	free_bloc(inumber);
	return inumber;
}

void free_blocs(unsigned int *bloc, unsigned int n) {
	int i;
	for(i=0; i < n ; i++) {
		if(blocs[i]){
			free_bloc(bloc[i]);
		}
	}
}
