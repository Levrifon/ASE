#include <stdlib.h>
#include <stdio.h>
#include "volume.h"
#include "drive.h"
#include "mbr.h"
#include <assert.h>


extern struct mbr_s mbr;

int create_vol(unsigned int nbloc){

        assert(mbr.mbr_magic == MBR_MAGIC);
        if(mbr.mbr_n_vol==MAX_VOL) {
                printf("Il y en a déjà %d/%d.",MAX_VOL,MAX_VOL);
                return 42;
        }

        //Où la nouvelle partition va commencer

        unsigned int new_cylinder,new_sector;

        new_cylinder = next_free_cylinder_of_bloc();
        new_sector = next_free_sector_of_bloc();

        //Création de la nouvelle partition
        struct vol_descr_s new_part;

        new_part.vol_nblocs = nbloc;
        new_part.vol_first_cylinder = new_cylinder;
        new_part.vol_first_sector = new_sector;
        mbr.mbr_vol[mbr.mbr_n_vol]=new_part;
        mbr.mbr_n_vol++;

        printf("Nouvelle partition de %d blocs sur la piste %d et au secteur %d (%d/%d)\n",nbloc,new_cylinder,new_sector,mbr.mbr_n_vol,MAX_VOL);

        write_mbr();
        return 0;

}

int main(int argc, char **argv){

        if (argc < 2) {
                printf("mkvol: missing argument\n./create_bloc [nbloc]\n");
                exit(42);
        }

        unsigned int nbloc = atoi(argv[1]);

        init_drive();
        read_mbr();
        return create_vol(nbloc);
  
}
