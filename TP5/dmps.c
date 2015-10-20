#include <assert.h>
#include "drive.h"

void dmps(unsigned int cylinder, unsigned int sector){
        char * buffer = (char *) malloc(HDA_SECTORSIZE);
        assert(buffer);
	//_____________________
	seek(cylinder, sector);
	
	//_______________________
	read_sector(cylinder, sector, buffer);
}

// DSHINFO #c #s taille secteur
// void chk_hardware(void){
// 	lire taille secteur via DSKINFO
//	compare à SECTORSIZE
// }

/*void main(int argc, char* argv){ // cylinder et sector sont dans args
	assert(argv==2);
	int16 cylinder = argv[0];
	int16 sector   = argv[1];
	init_hardware("config_hw.ini");
	dmps(cylinder, sector);
	afficher(MASTERBUFFER, SECTORSIZE);
}*/
