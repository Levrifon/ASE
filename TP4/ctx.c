#include "entete.h"


static void start_curr_ctx(void);
void init_ctx(struct ctx_s *, int, funct_t *, void*);

void yield(void) {
	if(curr_ctx != NULL) { /* si current existe on passe au contexte suivant */
		switch_to(curr_ctx->next_ctx);
	} else if (ctx_ring != NULL) { /* sinon si l'anneau existe */
		switch_to(ctx_ring);
	} else {
	        printf("debug yield\n");
		return; /* afficher un warning */
	}
}

void create_ctx(int stacksize, funct_t * f, void * args){
        struct ctx_s * ctx = (struct ctx_s*)malloc(sizeof(struct ctx_s));
        assert(ctx); // On vérifie que malloc n'a pas planté
        init_ctx(ctx, stacksize, f, args);
        if(ctx_ring == NULL){
                ctx_ring        = ctx;
                ctx->next_ctx   = ctx;
        } else {
                ctx->next_ctx           = ctx_ring->next_ctx;
                ctx_ring->next_ctx      = ctx;
        }
}

void switch_to(struct ctx_s * ctx){
        // Si ctx est main_ctx, c'est qu'on a vidé l'anneau des contextes
        // curr_ctx est donc null, et on se remet sur le contexte du main
        if( ctx == main_ctx ){
                curr_ctx = NULL;
                // On switch le contexte
                asm("movl %0, %%esp"
                "\n\t"
                "movl %1, %%ebp"
                :
                : "r"(main_ctx->ctx_esp),"r"(main_ctx->ctx_ebp)
                :);
                // Pour ne pas aller plus loin dans la fonction, puisqu'on a fini
                return;
        }
        
        assert( ctx->ctx_magic == CTX_MAGIC ); // On vérifie que le contexte est conforme
        
        // Boucle de nettoyage des contextes "morts"
	while(ctx->ctx_state == CTX_END || ctx->ctx_state == CTX_BL_SEM) {
		free(ctx->ctx_base); /* on libere la pile */
		curr_ctx->next_ctx = ctx->next_ctx; /* on rattache le prochain du contexte courant au prochain de ctx, le sortant de l'anneau */
		if(curr_ctx == ctx) { /*si il n'en reste plus qu'un */
			switch_to(main_ctx);    // On retourne au main
        		free(ctx);              // On nettoie le contexte inutile
        		return;                 // Et on s'arrête là
		}else{ /* sinon on continue */
		        ctx = curr_ctx->next_ctx;
                }
	}
	
	// On vérifie que la boucle de nettoyage a bien marché, et qu'on va executer un contexte pas fini
        assert( ctx->ctx_state == CTX_INIT ||
                ctx->ctx_state == CTX_EXE   );
        if(curr_ctx){ // Si on a déjà un contexte courant on l'enregistre
                asm("movl %%esp, %0"
                "\n\t"
                "movl %%ebp, %1"
                : "=r"(curr_ctx->ctx_esp),"=r"(curr_ctx->ctx_ebp)
                :
                :);
        } else { // Si on n'a pas de contexte courant on enregistre le contexte du main
                if(main_ctx==NULL){ // On enregistre juste le esp et ebp du main
                        main_ctx = (struct ctx_s*)malloc(sizeof(struct ctx_s));
                }
                asm("movl %%esp, %0"
                "\n\t"
                "movl %%ebp, %1"
                : "=r"(main_ctx->ctx_esp),"=r"(main_ctx->ctx_ebp)
                :
                :);
        }
                
        curr_ctx = ctx;
        // On switch le contexte
        asm("movl %0, %%esp"
        "\n\t"
        "movl %1, %%ebp"
        :
        : "r"(curr_ctx->ctx_esp),"r"(curr_ctx->ctx_ebp)
        :);
        
        if(curr_ctx->ctx_state == CTX_INIT){ // Si la fonction n'est pas lancée, on la lance
                start_curr_ctx();
        }
}

static void start_curr_ctx(void){
        curr_ctx->ctx_state = CTX_EXE;
        curr_ctx->ctx_f(curr_ctx->ctx_args);
        curr_ctx->ctx_state = CTX_END; // On précise au contexte que c'est fini
        yield();
}

void init_ctx(struct ctx_s *ctx, int stack_size, funct_t * f, void* args) {
        ctx->ctx_magic = CTX_MAGIC;
        assert(ctx->ctx_base = (char *)(malloc(stack_size)));
        ctx->ctx_f     = f;
        ctx->ctx_args  = args;
        ctx->ctx_state = CTX_INIT;
        ctx->ctx_esp   = ctx->ctx_base + stack_size - sizeof(int);
        ctx->ctx_ebp   = ctx->ctx_base + stack_size - sizeof(int);
}

