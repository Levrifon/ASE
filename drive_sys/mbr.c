#include <string.h>
#include <stdio.h>
#include "mbr.h"
#include "drive.h"

struct mbr_s mbr;

/* renvoie si le disque est déjà partitionné ou non */
int read_mbr(void) {
        //printf("debug mbr \n");
	char buffer[HDA_SECTORSIZE];
	read_sectorn(0,0,buffer,sizeof(struct mbr_s)); /* on lit au tout debut du secteur */
	memcpy(&mbr,buffer,sizeof(struct mbr_s)); /*on copie le resultat dans le mbr */
	//printf("read_mbr : %d == %d\n", mbr.mbr_magic, MBR_MAGIC);
	if(mbr.mbr_magic != MBR_MAGIC) {
	        printf("init mbr\n");
		mbr.mbr_magic = MBR_MAGIC;
		mbr.mbr_n_vol = 0;
		int i;
                for(i=0;i<MAX_VOL;i++) {
                        mbr.mbr_vol[i].vol_first_cylinder=0;
                        mbr.mbr_vol[i].vol_first_sector=0;
                        mbr.mbr_vol[i].vol_nblocs=1;
                        mbr.mbr_vol[i].vol_type=VOL_UNUSED;
                }
                write_mbr();
		return 0;
	}
	return 1;
}
/* permet d'écrire dans le mbr */
void write_mbr(void) {
	write_sectorn(0,0,(unsigned char*)&mbr,sizeof(mbr));
}


char* display_type(enum vol_type_e type){
	switch(type){
		case VOL_STD: return "Principale";
		case VOL_ANX: return "Etendue";
		default: return "Autre";
	}
}

void dump_vols(void){
        read_mbr();
	int i;
	printf("Volume\tCylindre\tSecteur\tNb blocs\tType\n-----------------------------------------------------------\n");
	for (i=0; i<mbr.mbr_n_vol; i++){
		printf("sda%d\t%d\t\t%d\t%d\t\t%s\n", 
			i,
			mbr.mbr_vol[i].vol_first_cylinder,
			mbr.mbr_vol[i].vol_first_sector,
			mbr.mbr_vol[i].vol_nblocs,
			display_type(mbr.mbr_vol[i].vol_type));
	}
}
