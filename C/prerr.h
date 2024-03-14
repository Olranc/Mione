#include <stdio.h>


int prerr(int line, char* msg) {
	printf("Hey! something wrong in line : %d ,it said : %s \n", line, msg);
	return 1;
}
