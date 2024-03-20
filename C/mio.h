#include <stdio.h>
#include <string.h>

#ifndef mio_h
#define mio_h



int mio(char* _case,int _type) { // HEAD,PROMOT,VALUE,SYMBOL
	char*heads[] = {
		"set",
		"input",
	};

	char* prompts[] = {
		"do",
		"then",
		"else",
	};

	for (int i = 0; i < sizeof(heads)/sizeof(char*); i=i+1) {
		
		if (strcmp(heads[i], _case)) {		
		}
		else {
			printf("pair\n");
		}
	}

	for (int i = 0; i < sizeof(prompts) / sizeof(char*); i = i + 1) {

		if (strcmp(prompts[i], _case)) {
		}
		else {
			printf("pair\n");
		}
	}
}
int newline() {

}

#endif
