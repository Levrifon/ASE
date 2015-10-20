#include "drive.h"

void frmt(int ncylinder,int nsector,int value) {
	int i,j;
	for(i = 0 ; i < ncylinder ; i++) {
		for(j = 0 ; j < nsector ; j++) {
			format_sector(i,j,value);
		}
	}
}
