#include "bloc.h"
#include "mbr.h"
#include <string.h>
#include <stdlib.h>
//static unsigned int current_vol;

void init_super(unsigned int vol, char name, unsigned int serial){
	super;// 		= (struct super_s*) malloc(sizeof(struct super_s));
	assert(super);
	first_bloc;// 	= (struct free_bloc_s*) malloc(sizeof(struct free_bloc_s));
	assert(first_bloc);

	super.super_first_free = 1;
	super.super_n_free = mbr.mbr_vol[vol].vol_nblocs-1; // Ou bien $CURRENT_VOLUME variable d'env du shell
	strncpy(super.super_name, &name, SUPER_NAME_MAX);
	super.super_serial = serial;
	super.super_magic  = SUPER_MAGIC;

	first_bloc.fb_size = super.super_n_free;
	first_bloc.fb_next = SUPER;

	save_super();
	write_bloc_n(1,&first_bloc, sizeof(struct free_bloc_s));
}

void save_super(void){
	assert(super.super_magic == SUPER_MAGIC);
	write_bloc_n(SUPER, &super, sizeof(struct super_s));
}
int load_super(unsigned int vol){
	char buffer[BLOCSIZE];
	read_bloc_n(SUPER, &buffer, sizeof(struct super_s));
	memcpy(&super, &buffer,sizeof(struct super_s));	
	return 0;
}

int load_first_free(void){
	read_bloc_n(super.super_first_free, &first_bloc, sizeof(first_bloc));
	return 0;
}

unsigned int new_bloc(){
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
		write_bloc_n(super.super_first_free, &first_bloc, sizeof(first_bloc));
	}
	// Peut être save_super();
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
	write_bloc_n(bloc, &bloc_s, sizeof(bloc_s));
	first_bloc = bloc_s;
}

