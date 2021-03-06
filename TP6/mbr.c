#include <string.h>
#include "mbr.h"
#include "drive.h"

extern struct mbr_s mbr;

/* renvoie si le disque est déjà partitionné ou non */
int read_mbr(void) {
	char buffer[HDA_SECTORSIZE];
	read_sectorn(0,0,buffer,sizeof(mbr)); /* on lit au tout debut du secteur */
	//read_sector_n(0,0,&mbr,sizeof(mbr));
	memcpy(&mbr,buffer,sizeof(mbr)); /*on copie le resultat dans le mbr */
	if(mbr.mbr_magic != MBR_MAGIC) {
		mbr.mbr_magic = MBR_MAGIC;
		mbr.mbr_n_vol = 0;
		int i;
                for(i=0;i<MAX_VOL;i++) {
                        mbr.vol[i].cylinder=0;
                        mbr.vol[i].sector=0;
                        mbr.vol[i].size=1;
                        mbr.vol[i].type=VOL_UNUSED;
                }
		return 0;
	}
	return 1;
}
/* permet d'écrire dans le mbr */
void write_mbr(void) {
	write_sector_n(0,0,&mbr,sizeof(mbr));
}


