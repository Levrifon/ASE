#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include "try.h"
static struct ctx_s *pctx;
static int mul(int depth) {
	int i;
	switch(scanf("%d", &i)) {
		case EOF :
			return 1; /*neutral element */
		case 0 :
			return mul(depth+1); /*get deeper because of error */
		case 1 :
			if(i)
				return i * mul(depth+1);
			else
				throw(pctx,0); /* ici utiliser le jump */
	}

}

int main() {
	int product;
	jmp_buf buf;
	pctx = malloc(2*sizeof(int));
	pctx->ctx_esp=0;
	pctx->ctx_ebp=0;
	printf("A list of int, please ! \n");
	printf("Resultat : %d \n" , try(pctx,mul,0)); /* avec 1\n2\n3 devrait retourner 6 */
}
