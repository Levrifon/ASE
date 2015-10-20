#ifndef _DRIVE_H_
#define _DRIVE_H_
#include "hardware.h"

void init_drive();
void seek(unsigned int cylinder, unsigned int sector);
void read_sector(unsigned int cylinder, unsigned int sector, unsigned char *buffer);
void write_sector(unsigned int cylinder, unsigned int sector, unsigned char *buffer);
void format_sector(unsigned int cylinder, unsigned int sector, unsigned int value);

#endif
