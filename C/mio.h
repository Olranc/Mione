#include <stdio.h>
#include <string.h>
#include "memory.h"


#ifndef mio_h
#define mio_h



int cSize = 0;
char*** c = NULL;


int setC(char*_type,char*_case,int*pas,int _t) {
	cSize++;
	
	if (c){
		c = realloc(c, cSize * sizeof(char*));
	}
	else {
		c = malloc(sizeof(char**));
	}
	c[cSize - 1] = malloc(sizeof(char*) * 2);
	c[cSize - 1][0] = malloc(strlen(_type) + 1);
	strcpy(c[cSize - 1][0], _type);
	if (strcmp("VALUE",_type)){

	}else{
		char* ma;
		cm(&ma,_case,_t);
		_case = ma;
	}
	c[cSize - 1][1] = malloc(strlen(_case) + 1);
	strcpy(c[cSize - 1][1], _case);
	*pas = 1;
	printf("%s %s\n", c[cSize - 1][0], c[cSize - 1][1]);
}

int mio(char* _case, int _type) { // HEAD,PROMOT,VALUE,VARIABLE,SYMBOL
	//HEAD:HEAD_NAME
	char* heads[] = {
		"set",
		"input",
	};

	char* prompts[] = {
		"do",
		"then",
		"else",
	};

	int pass = 0;


	for (int i = 0; i < sizeof(heads) / sizeof(char*); i = i + 1) {

		if (strcmp(heads[i], _case)) {
		}
		else {
			setC("HEAD", _case, &pass,_type);
		}
	}

	for (int i = 0; i < sizeof(prompts) / sizeof(char*); i = i + 1) {

		if (strcmp(prompts[i], _case)) {
		}
		else {
			setC("PROMPT", _case, &pass,_type);
		}
	}

	if (pass) {}
	else {
		if (_type == 6) {
			setC("VARIABLE", _case, &pass,_type);
		}
		if (_type==5){
			setC("VALUE",_case,&pass,_type);
		}
	}

	
}
int newline() {

}

#endif