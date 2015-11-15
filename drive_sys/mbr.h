#ifndef _MBR_H_
#define _MBR_H_

static struct mbr_s mbr;
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
	unsigned int mbr_n_vol;
	unsigned int mbr_magic;
};

int read_mbr();
void write_mbr();
void dump_vols(void);

#endif
