#include <stdio.h>
#include "try.h"

static int res;

int try(struct ctx_s *pctx, func_t *f, int arg) {
    
    asm("addl $8, %%esp"
	"\n\t"
	"movl %%esp, %0"
	"\n\t"
	"movl %%ebp, %1"
            :"=r"(pctx->ctx_esp), "=r"(pctx->ctx_ebp)
            :
            :);

    return f(arg);
}

int throw(struct ctx_s *pctx, int r) {
    res = r;
    asm("movl %0, %%esp" "\n\t" "movl %1, %%ebp"
            :
            :"r"(pctx->ctx_esp), "r"(pctx->ctx_ebp)
            :);

    return res;
}
