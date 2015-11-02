#ifndef _DRIVE_H_
#define _DRIVE_H_
#include "hardware.h"
#include "dump.h"

#define HDA_CMDREG      0x3F6
#define HDA_DATAREGS    0x110
#define HDA_MAXCYLINDER 16      
#define HDA_MAXSECTOR   16
#define HDA_IRQ         14
#define HDA_SECTORSIZE  256

void init_drive();
void seek(unsigned int cylinder, unsigned int sector);
void read_sector(unsigned int cylinder, unsigned int sector, unsigned char *buffer);
void write_sector(unsigned int cylinder, unsigned int sector, unsigned char *buffer);
void format_sector(unsigned int cylinder, unsigned int sector, unsigned int value);

#endif
