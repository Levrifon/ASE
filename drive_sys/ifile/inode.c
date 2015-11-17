#include "inode.h"
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
		read_bloc_n(inode.indirect,bloc,NBPB*sizeof(unsigned));
		free_blocs(bloc,&NBPB);
		free_bloc(inode.indirect);
	}
	if(inode.two_indirect) {
		unsigned bloc[NBPB];
		read_bloc_n(inode.two_indirect,bloc,NBPB*sizeof(unsigned));
		//a continuer
	}
	
}

void free_blocs(unsigned int bloc[], unsigned int n) {
	int i;
	for(i=0; i < n ; i++) {
		free_bloc(bloc[i]);
	}

}
