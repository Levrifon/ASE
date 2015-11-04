#include <string.h>
#include "mbr.h"

static struct mbr_s mbr;

/* renvoie si le disque est déjà partitionné ou non */
int read_mbr(void) {
	char buffer[HDA_SECTORSIZE];
	read_sectorn(0,0,buffer,sizeof(mbr)); /* on lit au tout debut du secteur */
	//read_sector_n(0,0,&mbr,sizeof(mbr));
	memcpy(&mbr,buffer,sizeof(mbr)); /*on copie le resultat dans le mbr */
	if(mbr.mbr_magic != MBR_MAGIC) {
		mbr.mbr_magic = MBR_MAGIC;
		/*mbr.mbr_n_vol = 0;*/
		return 0;
	}
	return 1;
}
/* permet d'écrire dans le mbr */
void write_mbr(void) {
	write_sector_n(0,0,&mbr,sizeof(mbr));
}

unsigned int cylinder_of_bloc(int vol, int bloc) {
	chk_disk();
	return (mbr.mbr_vol[vol].vol_first_cylinder + mbr.mbr_vol[vol].vol_first_sector + bloc) % HDA_MAXSECTOR;
}
unsigned int sector_of_bloc(int vol, int bloc) {
	chk_disk();
	return((mbr.mbr_vol[vol].vol_first_sector + bloc) % HDA_MAXSECTOR);
}

