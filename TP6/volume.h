#ifndef _VOL_H_
#define _VOL_H_

unsigned int cylinder_of_bloc(int vol, int bloc);
unsigned int sector_of_bloc(int vol, int bloc);
void read_bloc(unsigned int vol, unsigned nbloc, unsigned char * buffer);
void read_blocn(unsigned int vol, unsigned nbloc, unsigned char * buffer,unsigned int size);
void write_bloc(unsigned int vol, unsigned nbloc, const unsigned char * buffer);
void write_blocn(unsigned int vol, unsigned nbloc, const unsigned char * buffer, unsigned int size);
void format_vol(unsigned int vol, unsigned int nbloc, unsigned value);

#endif
