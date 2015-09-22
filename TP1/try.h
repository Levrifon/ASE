struct ctx_s {
	void * ctx_esp;
	void * ctx_ebp;
};

extern int try(struct ctx_s *pctx, func_t *f, int arg);
extern int throw(struct ctx_s *pctx, int r);
