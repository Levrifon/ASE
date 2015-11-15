#include <stdlib.h>
#include <stdio.h>
#include "volume.h"
#include "mbr.h"
#include "drive.h"
#include <assert.h>

extern struct mbr_s mbr;

/* Ancienne fonction qui dumpe juste le volume voulu, ne fait pas ce qu'on voudrait => comme df */
void dump_vol(unsigned int volume,unsigned int nbloc){
	int i,j;

	unsigned char *buffer=(char *) malloc(HDA_SECTORSIZE); 
        assert(buffer);
	read_bloc(volume,nbloc,buffer);

        dump(buffer,HDA_SECTORSIZE,0/*ascii*/,1/*octal*/);
}

int main(int argc, char **argv){
       	/* // Utilisé pour l'ancienne fonction
	if (argc < 3) {
                printf("dvol: missing argument\n./print_bloc [volume]\n");
                exit(42);
        }
        unsigned int volume = atoi(argv[1]);
	unsigned int nbloc = atoi(argv[2]);
	*/
        init_drive();
        read_mbr();
        dump_vols();
        return 0;
}
