#include <stdio.h>

void display_stack(void){
    int esp, ebp;
/* preciser un peu plus l'adresse des variables locales etc */
    asm ("movl %%esp, %0" "\n\t" "movl %%ebp, %1"

               : "=r"(esp), "=r"(ebp)  /* outputs */
               
               : /* empty inputs */

               : );

    printf("ebp : %p\n",ebp);
    printf("esp : %p\n",esp);
    return;
}
