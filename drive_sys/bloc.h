#ifndef __BLOC_H__
#define __BLOC_H__

#define SUPER_MAGIC 0xDEADC0DE
#define SUPER 0
#define SUPER_NAME_MAX 32
#define BLOCSIZE 255
#include "mbr.h"
#include "drive.h"
#include "volume.h"
struct super_s{
	unsigned int 	super_first_free;
	unsigned int 	super_n_free;
	unsigned int 	super_magic;
	//unsigned int 	super_root_inum;
	//unsigned int 	super_root_inode;
	char 		super_name[SUPER_NAME_MAX];
	unsigned int 	super_serial;
};

struct free_bloc_s{
	unsigned int fb_size;
	unsigned int fb_next;
};	

static struct super_s super;
static struct free_bloc_s first_bloc;

void init_super(unsigned int vol, char name, unsigned int serial);
void save_super(void);
int load_super(unsigned int vol);
int load_first_free(void);
unsigned int new_bloc(void);
void free_bloc(unsigned int bloc);
float used_percents(unsigned int vol);
void display_infos(void);

#endif
