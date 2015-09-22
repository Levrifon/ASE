#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "try.h"

int try(struct ctx_s *pctx, func_t *f, int arg) {
    
    asm("movl %%esp, %0" "\n\t" "movl %%ebp, %1"
            :"=r"(pctx->ctx_esp), "=r"(pctx->ctx_ebp)
            :
            :);


    return 0;
}

int throw(struct ctx_s *pctx, int r) {
       
    asm("movl %0, %%esp" "\n\t" "movl %1, %%ebp"
            :
            :"r"(pctx->ctx_esp), "r"(pctx->ctx_ebp)
            :);
 
    return r;
}
