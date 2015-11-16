#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bloc.h"

int main() {
	printf("Super loaded ? %d", load_super(0));
	display_infos();
	return 0;
}
