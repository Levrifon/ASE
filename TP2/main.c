#include "entete.h"
struct ctx_s ctx_ping;
struct ctx_s ctx_pong;
struct ctx_s ctx_pang;

void f_ping(void *arg);
void f_pong(void *arg);
void f_pang(void *arg);

int main(int argc, char* argv[]) {
	init_ctx(&ctx_ping,16384,f_ping,NULL);
	init_ctx(&ctx_pong,16384,f_pong,NULL);
	init_ctx(&ctx_pang,16384,f_pang,NULL);
	switch_to(&ctx_ping); /* execute the context's function of ping */

	exit(EXIT_SUCCESS);
}

void f_ping(void *args) {
	while(1) {
		printf("A");
		switch_to(&ctx_pong);
		printf("B");
		switch_to(&ctx_pong);
		printf("C");
		switch_to(&ctx_pong);
	}
}

void f_pong(void *args) {
	while(1) {
		printf("1");
		switch_to(&ctx_pang);
		printf("2");
		switch_to(&ctx_pang);
	}
}

void f_pang(void *args) {
	while(1) {
		printf("$");
		switch_to(&ctx_ping);
		printf("£");
		switch_to(&ctx_ping);
	}
}
