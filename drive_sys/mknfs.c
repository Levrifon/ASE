#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bloc.h"

int main(){
	int vol;
	int nom;
	int nbblocs;
	int i;
	unsigned int test_serial = 0xDEADBEEF;
        init_drive();
	read_mbr();
	dump_vols();

	printf("Saisir le numero du volume:\n");
	scanf("%i", &vol);
	while (mbr.mbr_vol[vol].vol_nblocs == 0){
		printf("Veuillez saisir un  numero de volume valide:\n");
		scanf("%i", &vol);
	}
	printf("Saisir le nom:\n");
	scanf("%i", &nom);
	init_super(vol, nom, test_serial);

	printf("Saisir le nombre de blocs:\n");
	scanf("%i", &nbblocs);

	for (i=0; i<nbblocs; i++){
		new_bloc();
	}

	save_super();
	if (nbblocs > mbr.mbr_vol[vol].vol_nblocs-1){
		nbblocs = mbr.mbr_vol[vol].vol_nblocs-1;
	}
	printf("Superbloc rempli de %d blocs !\n", nbblocs);
	printf("Taux d'occupation : %f/100\n", used_percents(vol));

	return 0;
}
