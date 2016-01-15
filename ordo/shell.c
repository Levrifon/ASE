#include "shell.h"
#include "ps.c"
#include "ls.c"
#define TAILLE 256

char** parsecmd(char* cmd) {
	char** res;
	res = strtok(cmd," ");
	return res;
}

void shell(void *args) {
	char * cmd = calloc(TAILLE+1, sizeof *cmd);
	int c;
	while(1){
		printf("£ ");
		scanf("%80[^\n]",cmd);
		while ( ((c = getchar()) != '\n') && c != EOF);
		/*printf("Your command is %s.\n", cmd);*/
		mycall(cmd);
	}
}


void mycall(struct cmd_s *cmd) {
	char** cmd_args;
	if(cmd->cmd_name == NULL) { return; }
	cmd_args = parsecmd(cmd->cmd_name);
	execvp(cmd_args[0],cmd_args+1);
}


