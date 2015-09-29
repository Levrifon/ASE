#include "entete.h"

void init_ctx(struct ctx_s *ctx, int stack_size, funct_t * f, void* args) {
	ctx->ctx_magic = CTX_MAGIC;
    	assert(ctx->ctx_base = (char *)(malloc(stack_size)));
	ctx->ctx_f     = f;
	ctx->ctx_args  = args;
	ctx->ctx_state = CTX_INIT;
	ctx->ctx_esp   = ctx->ctx_base + stack_size - sizeof(int);
    ctx->ctx_ebp   = ctx->ctx_base + stack_size - sizeof(int);

}
