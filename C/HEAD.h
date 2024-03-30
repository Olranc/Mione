#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "CASE_type.h"

#ifndef HEAD_h
#define HEAD_h



int set(char*** _while,int _whileSize) { //1
	for (int i = 0; i < _whileSize; i++) {
		_while[i];
	}
}

int vI(char** v, char* HEADNAME) {
	for (int i = 0; i < sizeof(HEADS) / sizeof(char*); i++) {
		if (strcmp(HEADNAME, HEADS[i])) {}else{
			*v = malloc(sizeof((i+1)/10+2));
			sprintf(*v,"%d",i+1);
		}
	}
}

#endif 
