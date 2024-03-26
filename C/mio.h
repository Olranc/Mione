#include <stdio.h>
#include <string.h>
#include "memory.h"


#ifndef mio_h
#define mio_h

int pass = 0;

int cSize = 0;
char*** c = NULL;


int setC(char* _type, char* _case, int _t) {
	cSize++;

	if (c) {
		c = realloc(c, cSize * sizeof(char*));
	}
	else {
		c = malloc(sizeof(char**));
	}
	c[cSize - 1] = malloc(sizeof(char*) * 2);
	c[cSize - 1][0] = malloc(strlen(_type) + 1);
	strcpy(c[cSize - 1][0], _type);

	if (strcmp("VALUE", _type)) {

	}
	else {
		char* ma;
		cm(&ma, _case, _t);
		_case = ma;
		
	}
	
	c[cSize - 1][1] = malloc(strlen(_case) + 1);
	strcpy(c[cSize - 1][1], _case);
	
	printf("%s %s\n", c[cSize - 1][0], c[cSize - 1][1]);

	pass = 1;
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

	printf("| [CASE]:`%s`				[TYPE]:`%d`| \n", _case, _type);
	pass = 0;

	for (int i = 0; i < sizeof(heads) / sizeof(char*); i = i + 1) {

		if (strcmp(heads[i], _case)) {
		}
		else {
			setC("HEAD", _case, _type);
		}
	}

	for (int i = 0; i < sizeof(prompts) / sizeof(char*); i = i + 1) {

		if (strcmp(prompts[i], _case)) {
		}
		else {
			setC("PROMPT", _case, _type);
		}
	}

	if (pass) {  }
		
	else {
		if (_type == 6) {
			setC("VARIABLE", _case, _type);
		}
		if (_type == 2 || _type == 3 || _type == 4 || _type == 5 || _type == 8) {
			setC("VALUE", _case, _type);
		}
	}


}
int newline() {

}

#endif