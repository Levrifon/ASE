#ifndef _MBR_H_
#define _MBR_H_

#include "drive.h"

enum vol_type_e {VOL_STD,VOL_ANX,VOL_OTHER,VOL_UNUSED};
#define MBR_MAGIC 0xDEADC0DE
#define MAX_VOL 8

struct vol_descr_s {
	unsigned int vol_first_cylinder;
	unsigned int vol_first_sector;
	unsigned int vol_nblocs;
	enum vol_type_e vol_type;
};

struct mbr_s {
	struct vol_descr_s mbr_vol[MAX_VOL];
	unsigned mbr_magic;
};

extern int read_mbr();


#endif
