#include "entete.h"
#include "shell.h"
/*
void f_ping(void *arg);
void f_pong(void *arg);
void f_pang(void *arg);
*/
void shell(void *args);
/*
int main(int argc, char* argv[]) {
	create_ctx(16384,f_ping,NULL);
	create_ctx(16384,f_pong,NULL);
	create_ctx(16384,f_pang,NULL);
	yield();
	printf("Fini !\n");
	exit(EXIT_SUCCESS);
}

*/
int main(int argc,char* argv[]) {
	create_ctx(16384,shell,NULL);
}
/*void f_ping(void *args) {
	int i;
	for(i=0; i<100; i++){
		printf("A");
		yield();
		printf("B");
		yield();
		printf("C");
		yield();
	}
	printf("\nfini ping\n");
}

void f_pong(void *args) {
	int i;
	for(i=0; i<300; i++){
		printf("1");
		yield();
		printf("2");
		yield();
	}
	printf("\nfini pong\n");
}

void f_pang(void *args) {
	int i;
	for(i=0; i<200; i++){
		printf("$");
		yield();
		printf("£");
		yield();
	}
	printf("\nfini pang\n");
}*/
