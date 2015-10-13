#include "sem.h"
#include "entete.h"

void sem_init(struct sem_s *sem, unsigned int val){
	//sem = (struct sem_s *) malloc(sizeof(struct sem_s));
	//assert(sem);
	sem->tokens = val;
	sem->first_ctx_bl = NULL;
}

void sem_down(struct sem_s *sem){
	sem->tokens--;
	if(sem->tokens < 0){
		curr_ctx->ctx_state = CTX_BL_SEM;
		curr_ctx->next_sem_bl=sem->first_ctx_bl;
		sem->first_ctx_bl->next_ctx = curr_ctx;
		yield(); // Modifier yield ou switch_to pour ne pas donner la main à un ctx à CTX_BL_SEM
	}
}

void sem_up(struct sem_s *sem){
	sem->tokens++;
	if(sem->tokens <= 0){
		//struct ctx_s * tmp;
		sem->first_ctx_bl->ctx_state = CTX_EXE;
		//tmp = sem->first_ctx;
		sem->first_ctx_bl=sem->first_ctx_bl->next_ctx;
		//tmp->next_sem_bl = NULL;
		//yield();
	}
}
