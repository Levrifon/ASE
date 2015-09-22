#include <setjmp.h>
#include <stdio.h>
static int mul(int depth) {
	int i;
	switch(scanf("%d", &i)) {
		case EOF :
			return 1; /*neutral element */
		case 0 :
			return mul(depth+1);
		case 1 :
			if(i)
				return i * mul(depth+1);
			else
				return 0;
	}

}

int main() {
	int product;
	static jump_buf buf;
	struct ctx_s *pctx;
	printf("A list of int, please ! \n");
	/* try(mul(0)) */
}
