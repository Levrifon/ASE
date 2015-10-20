#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "drive.h"

int check_values(unsigned int cylinder, unsigned int sector){
        assert(cylinder < HDA_MAXCYLINDER);
        assert(sector   < HDA_MAXSECTOR);
}

void empty_fct(){
        return;
}

void init_drive(){
        int i;
        assert(init_hardware("hardware.ini") != 0);
        for(i=0;i<16;i++){
                IRQVECTOR[i]=empty_fct;
        }
}

void seek(unsigned int cylinder, unsigned int sector){
        check_values(cylinder, sector); // Seek est utilisé partout, on peut donc mettre check ici
	//deplacer tete lecture
	//ecrire cylinder et sector dans les ports de donnees [ cyl Fort | cyl faible | sec Fort | sec faible ]
	_out(HDA_DATAREGS  , (cylinder>>8)&0xFF);
	_out(HDA_DATAREGS+1,  cylinder    &0xFF);
	_out(HDA_DATAREGS+2, (sector>>8)  &0xFF);
	_out(HDA_DATAREGS+3,  sector      &0xFF);
	//ecrire SEEK dans le port de commande
	_out(HDA_CMDREG, CMD_SEEK);
	//attendre HDA_IRQ
	_sleep(HDA_IRQ);
}
void read_sector(unsigned int cylinder, unsigned int sector, unsigned char *buffer){
        seek(cylinder, sector)
	//lire le secteur courant
	//ecrire 1 dans le port de données [ 0 | 1 ]
	_out(HDA_DATAREGS  , 0);
	_out(HDA_DATAREGS+1, 1);
	//ecrire READ dans le port de commande
	_out(HDA_CMDREG, CMD_READ);
	//attendre HDA_IRQ
	_sleep(HDA_IRQ);
}
void write_sector(unsigned int cylinder, unsigned int sector, unsigned char *buffer){
        seek(cylinder, sector);
        //mettre buffer dans le masterbuffer
        memcpy(MASTERBUFFER, buffer, HDA_SECTORSIZE);
        //ecrire 1 dans le port de données
        _out(HDA_DATAREGS,0);
        _out(HDA_DATAREGS+1,1);
        //ecrire WRITE dans le port de commande
        _out(HDA_CMDREG,CMD_WRITE);
        _sleep(HDA_IRQ);
}
void format_sector(unsigned int cylinder, unsigned int sector, unsigned int value){
        seek(cylinder, sector);
        // Mettre 1 dans le port de données ( on ne veut qu'un secteur de formaté )
        _out(HDA_DATAREGS,0);
        _out(HDA_DATAREGS+1,1);
        // Mettre value dans le port de données
        _out(HDA_DATAREGS+2,(value>>24) & 0xFF);
        _out(HDA_DATAREGS+3,(value>>16) & 0xFF);
        _out(HDA_DATAREGS+4,(value>>8) & 0xFF);
        _out(HDA_DATAREGS+5,value & 0xFF);
        // ecrire FORMAT dans le port de commande
        _out(HDA_CMDREG,CMD_FORMAT);
        _sleep(HDA_IRQ);
}

