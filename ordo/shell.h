#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "entete.h"
struct cmd_s {
	char* cmd_name;
	funct_t* func;
	char* help_text;
};


extern void shell(void *args);
extern void mycall(struct cmd_s* cmd);

