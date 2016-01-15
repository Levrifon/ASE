#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TAILLE 80


int main(int argc, char * argv[]){
        char * cmd = calloc(TAILLE+1, sizeof *cmd);
        int c;
        while(1){
                printf("£ ");
                scanf("%80[^\n]",cmd);
                while ( ((c = getchar()) != '\n') && c != EOF);
                printf("Your command is %s.\n", cmd);
        }
}
