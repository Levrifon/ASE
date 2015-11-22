#include "bloc.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
unsigned int current_vol;// Ou bien $CURRENT_VOLUME variable d'env du shell

void init_super(unsigned int vol, char name, unsigned int serial){
	//super;// 		= (struct super_s*) malloc(sizeof(struct super_s));
	//first_bloc;// 	= (struct free_bloc_s*) malloc(sizeof(struct free_bloc_s));

	super.super_first_free = 1;
	super.super_n_free = mbr.mbr_vol[vol].vol_nblocs-1;
	strncpy(super.super_name, &name, SUPER_NAME_MAX);
	super.super_serial = serial;
	super.super_magic  = SUPER_MAGIC;
	current_vol = vol; // A changer si on utiliser une variable d'env

	first_bloc.fb_size = super.super_n_free;
	first_bloc.fb_next = SUPER;

	save_super();
	write_blocn(current_vol, 1, (unsigned char *)&first_bloc, sizeof(struct free_bloc_s));
}

void save_super(void){
	assert(super.super_magic == SUPER_MAGIC);
	write_blocn(current_vol, SUPER, (unsigned char *) &super, sizeof(struct super_s));
}

int load_super(unsigned int vol){
	char buffer[BLOCSIZE];
	read_blocn(vol, SUPER, (unsigned char *)&buffer, sizeof(struct super_s));
	memcpy(&super, &buffer,sizeof(struct super_s));
	current_vol = vol; // A changer si on utiliser une variable d'env
	if(super.super_magic == SUPER_MAGIC){
		return 0;
	}
	return 1;
}

int load_first_free(void){
	if(super.super_n_free == 0){
		return 0;
	}
	read_blocn(current_vol, super.super_first_free, (unsigned char *)&first_bloc, sizeof(first_bloc));
	return 1;
}

unsigned int new_bloc(void){
	if(super.super_n_free == 0){
		return 0;
	}
	unsigned int res;
	load_first_free();
	res = super.super_first_free;
	super.super_n_free--;
	if(first_bloc.fb_size == 1){
		super.super_first_free=first_bloc.fb_next;
	}else{
		super.super_first_free++;
		first_bloc.fb_size--;
		write_blocn(current_vol, super.super_first_free, (unsigned char *)&first_bloc, sizeof(first_bloc));
	}
	save_super();
	return res;
	// donner bloc en tête du premier bloc libre, modifier le bloc d'après et l'écrire
	// Si le bloc en tête est seul il faut changer le superbloc pour changer le first_free_bloc
	// Si aucun bloc retourner 0
}

void free_bloc(unsigned int bloc){
	struct free_bloc_s bloc_s;
	bloc_s.fb_size = 1;
	bloc_s.fb_next = super.super_first_free;
	super.super_first_free = bloc;
	write_blocn(current_vol, bloc, (unsigned char *)&bloc_s, sizeof(bloc_s));
	first_bloc = bloc_s;
	save_super();
}

float used_percents(unsigned int vol){
	return (1.00 - (float)super.super_n_free/(float)(mbr.mbr_vol[vol].vol_nblocs-1))*100.00;
}

void display_infos(void){
	printf("Nombre de blocs : %d\nNom\tSerial\tTaille\tUtilisé\tDispo.\tPourcentage\n%s\t%d\t%d\t%d\t%d\t%f\n",
			mbr.mbr_vol[current_vol].vol_nblocs-1-super.super_n_free,
			super.super_name,
			super.super_serial,
			mbr.mbr_vol[current_vol].vol_nblocs-1,
			mbr.mbr_vol[current_vol].vol_nblocs-1-super.super_n_free,
			super.super_n_free,
			used_percents(current_vol));
}
