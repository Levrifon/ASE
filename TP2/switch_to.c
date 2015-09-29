#include "entete.h"

static struct ctx_s * curr_ctx;
static struct ctx_s * main_ctx;

static void start_curr_ctx(void);

void switch_to(struct ctx_s * ctx){
    assert( ctx->ctx_magic == CTX_MAGIC );
    assert( ctx->ctx_state == CTX_INIT ||
            ctx->ctx_state == CTX_EXE   );
    if(curr_ctx){ // Si on a déjà un contexte courant
        asm("movl %%esp, %0"
            "\n\t"
            "movl %%ebp, %1"
            : "=r"(curr_ctx->ctx_esp),"=r"(curr_ctx->ctx_ebp)
            :
            :);
    } else { // Sinon, on vient du main et on sauvegarde le contexte du main
        main_ctx = (struct ctx_s *)malloc(sizeof(struct ctx_s));
        asm("movl %%esp, %0"
            "\n\t"
            "movl %%ebp, %1"
            : "=r"(main_ctx->ctx_esp),"=r"(main_ctx->ctx_ebp)
            :
            :);

    }
    curr_ctx = ctx;
    // On switch le contexte
    if(curr_ctx->ctx_state == CTX_INIT){ // Si la fonction n'est pas lancée, on la lance
        start_curr_ctx();
    } else { // Si elle est lancée, on switch
        asm("movl %0, %%esp"
            "\n\t"
            "movl %1, %%ebp"
            :
            : "r"(curr_ctx->ctx_esp),"r"(curr_ctx->ctx_ebp)
            :);
    }
}

static void start_curr_ctx(void){
    curr_ctx->ctx_state = CTX_EXE;
    curr_ctx->ctx_f(curr_ctx->ctx_args);
    curr_ctx->ctx_state = CTX_END; // On précise au contexte que c'est fini
    // On retourne au main
    asm("movl %0, %%esp"
        "\n\t"
        "movl %1, %%ebp"
        :
        : "r"(main_ctx->ctx_esp),"r"(main_ctx->ctx_ebp)
        :);
}
