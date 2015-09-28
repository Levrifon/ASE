#include <stdio.h>
static char* var_glob = "variable globale";
void display_stack(void){
    int esp, ebp;
    char* var_loc = "variable locale";
/* preciser un peu plus l'adresse des variables locales etc */
    asm ("movl %%esp, %0" "\n\t" "movl %%ebp, %1"

               : "=r"(esp), "=r"(ebp)  /* outputs */
               
               : /* empty inputs */

               : );

	printf("ebp : %p\n",ebp);
	printf("esp : %p\n",esp);
	printf("%s : %p\n",var_glob,&var_glob); /* variable globale située ailleurs de la pile */
	printf("%s : %p\n",var_loc,&var_loc); /* variable locale dans la pile */

    return;
}
