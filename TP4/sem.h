#ifndef SEMH
#define SEMH

struct sem_s{
	int tokens;
	struct ctx_s * first_ctx_bl;
};

void sem_init(struct sem_s *sem, unsigned int val);

void sem_down(struct sem_s *sem);

void sem_up(struct sem_s *sem);

#endif

/*
	switch_to(ctx){
		while(state=END ou BL_SEM et que j'ai pas fait le tour)
			ctx=ctx->ctx_next;
		retourner au main
*/
