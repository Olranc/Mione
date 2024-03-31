#include <stdio.h>
#include <string.h>
#include "memory.h"

#include "run.h"
#include "CASE_type.h"

#ifndef mio_h
#define mio_h

int pass = 0;
int cSize = 0;

char**** c;
int NumOfLine = 0;

// set							x								=								"hello"
// <HEAD ID>    <虛擬記憶體位置>     <記憶體位置>		<虛擬記憶體位置>

// "a"=="a"
// <虛擬記憶體位置> <符號ID> <虛擬記憶體位置>

int setC(char* _type, char* _case, int _t) {
	c = Rut ? &Runthions : &MIO;

	//printf("hey i am %s and %s or %d\n", _type, _case, _t);
	cSize++;

	if (*c) {
		*c = realloc((*c), cSize * sizeof(char**));
	}
	else {
		*c = malloc(sizeof(char**));
	}

	(*c)[cSize - 1] = malloc(sizeof(char*) * 2);

	(*c)[cSize - 1][0] = malloc(strlen(_type) + 1);
	strcpy((*c)[cSize - 1][0], _type);

	


	if (strcmp("VARIABLE", _type)) {}
	else {
		char* ma;
		cm(&ma, _case, _t);
		_case = ma;
	}
	if (strcmp("VALUE", _type)) {}
	else {
		char* ma;
		cm_v(&ma, _t, _case);
		_case = ma;
	}

	if (strcmp("HEAD", _type)) {}
	else {
		char* ma;
		vI("HEAD", &ma, _case);
		_case = ma;
	}

	if (strcmp("PROMPT", _type)) {}
	else {
		char* ma;
		vI("PROMPT", &ma, _case); 
		_case = ma;
	}

	if (strcmp("SYMBOL", _type)) {}
	else {
		char* ma;
		vI("SYMBOL", &ma, _case); 
		_case = ma;
	}

	



	(*c)[cSize - 1][1] = malloc(strlen(_case) + 1);
	strcpy((*c)[cSize - 1][1], _case);

	//printf("%s %s\n", *c[cSize - 1][0], *c[cSize - 1][1]);

	pass = 1;
}

int mio(char* _case, int _type) { // HEAD,PROMOT,VALUE,VARIABLE,SYMBOL
	//HEAD:HEAD_NAME

	//printf("[CASE]:`%s`				[TYPE]:`%d` \n", _case, _type);
	pass = 0;

	for (int i = 0; i < sizeof(HEADS) / sizeof(char*); i = i + 1) {

		if (strcmp(HEADS[i], _case)) {
		}
		else {
			setC("HEAD", _case, _type);
		}
	}

	if (pass) {}else{
		for (int i = 0; i < sizeof(PROMOTS) / sizeof(char*); i = i + 1) {

			if (strcmp(PROMOTS[i], _case)) {
			}
			else {
				setC("PROMPT", _case, _type);
			}
		}
	}
	if (pass) {}else{
		for (int i = 0; i < sizeof(SYMBOLS) / sizeof(char*); i = i + 1) {

			if (strcmp(SYMBOLS[i], _case)) {
			}
			else {
				setC("SYMBOL", _case, _type);
			}
		}
	}
	

	

	if (pass) { 
		
	}
		
	else {
		if (_type == 6) {
			setC("VARIABLE", _case, _type);
		}
		if (_type == 2 || _type == 3 || _type == 4 || _type == 5 || _type == 8) {
			setC("VALUE", _case, _type);
		}
	}
	
	char* result = strstr(_case, "\n");
	if (result != NULL) { //我知道這樣用之後會有很多問題
		NumOfLine++;
		if (everyLines) {
			everyLines = realloc(everyLines, sizeof(int) * NumOfLine);
		}
		else {
			everyLines = malloc(sizeof(int) * 1);
		}

		everyLines[NumOfLine - 1] = the_size;
		
	}

	if (pass) {
		the_size++;
		//printf("<數值與類型>: `%s` `%s`\n", c[cSize - 1][0], c[cSize - 1][1]);
	}
	
}

#endif