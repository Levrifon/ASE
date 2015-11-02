/* ------------------------------
   $Id: mkhd.c,v 1.4 2004/10/12 09:16:57 marquet Exp $
   ------------------------------------------------------------

   Create and intialize a drive using the hardware simulator.
   Philippe Marquet, october 2002

   A minimal example of a program using the ATA interface.
   It is given to the students as such.
   
*/

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "drive.h"

int main(int argc, char **argv){
	/*unsigned int i;
	assert(argc > 1);*/
	/* init hardware */
	init_drive();
	
	

	

	/* and exit! */
	exit(EXIT_SUCCESS);
}
