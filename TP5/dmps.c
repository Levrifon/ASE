#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "drive.h"

void dmps(unsigned int cylinder, unsigned int sector){
        char * buffer = (char *) malloc(HDA_SECTORSIZE);
        assert(buffer);
	//_____________________
	seek(cylinder, sector);
	
	//_______________________
	read_sector(cylinder, sector, buffer);
	
        dump(buffer,HDA_SECTORSIZE,0/*ascii*/,1/*octal*/);
}

int main(int argc, char **argv){

	if (argc < 3) {
	        printf("dmps: missing arguments\n./dmps [cylinder] [sector]\n");
	        exit(42);
	}
	unsigned int cylinder = atoi(argv[1]);
	unsigned int sector = atoi(argv[2]);

	init_drive();  
	dmps(cylinder,sector); 

	return 0;
  
}

// DSKINFO #c #s taille secteur
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
