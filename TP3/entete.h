#ifndef ENTETE
#define ENTETE

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
enum ctx_state_e {CTX_INIT,CTX_EXE,CTX_END};
#define CTX_MAGIC 0xDEADC0DE
typedef void (funct_t)(void*);

struct ctx_s {
	void* ctx_esp;
	void* ctx_ebp;
	int stack_size;
	funct_t * ctx_f;
	char* ctx_base;
	void* ctx_args;
	enum ctx_state_e ctx_state;
	unsigned int ctx_magic; /* detrompeur */
	struct ctx_s* next_ctx;
};

extern void init_ctx(struct ctx_s* ctx,int stack_size, funct_t * f, void* args);
extern void yield();
extern void create_ctx(int stacksize, funct_t * f, void * args);
extern void switch_to(struct ctx_s * ctx);

#endif // ENTETE
