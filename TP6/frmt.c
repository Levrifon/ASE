#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "drive.h"

void frmt(int ncylinder,int nsector,int value) {
	int i,j;
	for(i = 0 ; i < ncylinder ; i++) {
                for(j = 0 ; j < nsector ; j++) {
			format_sector(i,j,value);
		}
	}
}


int main(int argc, char **argv){

	if (argc < 2) {
	        printf("frmt: missing arguments\n./frmt [value]\n");
	        exit(42);
        }

	unsigned int value = atoi(argv[1]);

	init_drive();  
	frmt(HDA_MAXCYLINDER,HDA_MAXSECTOR,value);

	return 0;
  
}
