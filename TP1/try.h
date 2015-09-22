struct ctx_s {
	void * ctx_esp;
	void * ctx_ebp;
};

typedef int (func_t)(int); /* fonction qui retourne un int depuis un int en entree */

extern int try(struct ctx_s *pctx, func_t *f, int arg);
extern int throw(struct ctx_s *pctx, int r);
