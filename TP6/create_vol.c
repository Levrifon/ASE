#include <stdlib.h>
#include <stdio.h>
#include "volume.h"
#include "mbr.h"
#include <assert.h>


extern struct mbr_s mbr;

int create_vol(unsigned int nbloc){

        assert(mbr.magic == MAGIC_MBR);
        if(mbr.nb_vol==MAX_VOL) {
                printf("Il y en a déjà %d/%d.",MAX_VOL,MAX_VOL);
                return 42;
        }

        //Où la nouvelle partition va commencer

        unsigned int new_cylinder,new_sector;

        new_cylinder = next_free_cylinder_of_bloc();
        new_sector = next_free_sector_of_bloc();

        //Création de la nouvelle partition
        struct vol_descr_s new_part;

        new_part.size = nbloc;
        new_part.cylinder = new_cylinder;
        new_part.sector = new_sector;
        mbr.vol[mbr.nb_vol]=new_part;
        mbr.nb_vol++;

        printf("Nouvelle partition de %d blocs sur la piste %d et au secteur %d (%d/%d)\n",nbloc,new_cylinder,new_sector,mbr.nb_vol,MAX_VOL);

        save_mbr();
        return 0;

}

int main(int argc, char **argv){

        if (argc < 2) {
                printf("create_vol: missing argument\n./create_bloc [nbloc]\n");
                exit(~69);
        }

        unsigned int nbloc = atoi(argv[1]);

        init_driver();
        read_mbr();
        return create_vol(nbloc);
  
}
