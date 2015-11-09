#include "mbr.h"
#include "drive.h"
#include "volume.h"

unsigned int cylinder_of_bloc(int vol, int bloc) {
	chk_disk();
	return (mbr.mbr_vol[vol].vol_first_cylinder + mbr.mbr_vol[vol].vol_first_sector + bloc) % HDA_MAXSECTOR;
}
unsigned int sector_of_bloc(int vol, int bloc) {
	chk_disk();
	return((mbr.mbr_vol[vol].vol_first_sector + bloc) % HDA_MAXSECTOR);
}

unsigned int next_free_cylinder_of_bloc(){
        unsigned int res;
        int vol = mbr.nb_vol?mbr.nb_vol-1:mbr.nb_vol;
        assert(mbr.magic==MAGIC_MBR);
        assert(vol+1<MAX_VOL);
        res = cylinder_of_bloc(vol,mbr.vol[vol].size+1);
        if(res == NB_CYLINDER){
                return 0;
        }
        return res;
}

unsigned int next_free_sector_of_bloc(){
        unsigned int res;
        int vol = mbr.nb_vol?mbr.nb_vol-1:mbr.nb_vol;
        assert(mbr.magic==MAGIC_MBR);
        assert(vol+1<MAX_VOL);
        res = sector_of_bloc(vol,mbr.vol[vol].size+1);
        if(res == NB_SECTOR){
                return 0;
        }
        return res;
}

void read_bloc(unsigned int vol, unsigned int nbloc, unsigned char * buffer){
        read_sector(cylinder_of_bloc(vol,nbloc), sector_of_bloc(vol,nbloc), buffer);
}

void read_blocn(unsigned int vol, unsigned int nbloc, unsigned char * buffer,unsigned int size){
        read_sectorn(cylinder_of_bloc(vol,nbloc), sector_of_bloc(vol,nbloc), buffer,size);
}

void write_bloc(unsigned int vol, unsigned int nbloc, const unsigned char * buffer){
        write_sector(cylinder_of_bloc(vol,nbloc), sector_of_bloc(vol,nbloc), buffer);
}

void write_blocn(unsigned int vol, unsigned int nbloc, const unsigned char * buffer, unsigned int size){
        write_sectorn(cylinder_of_bloc(vol,nbloc), sector_of_bloc(vol,nbloc), buffer,size);
}

void format_vol(unsigned int vol, unsigned int nbloc, unsigned value){
        format_sector(cylinder_of_bloc(vol,nbloc), sector_of_bloc(vol,nbloc), 0);
}
