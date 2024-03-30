#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef CASE_type_h
#define CASE_type_h

char* HEADS[] = {
	"input",
	"set",
	
};

char* PROMOTS[] = {
	"do",
	"then",
	"else",
	"=",
};

char* SYMBOLS[] = {
	"==",
	"-",
	"+",
	"^",
	"*",
	"/"
};

int vI(char* _type,char** v, char* NAME) {
	char** c = (strcmp(_type, "HEAD") ? (strcmp(_type, "PROMPT") ? (strcmp(_type, "SYMBOL") ? NULL : SYMBOLS) : PROMOTS) : HEADS);

	int size = (strcmp(_type, "HEAD") ? (strcmp(_type, "PROMPT") ? (strcmp(_type, "SYMBOL") ? 0 : sizeof(SYMBOLS)) : sizeof(PROMOTS)) : sizeof(HEADS))/sizeof(char*);
	if (c != NULL) {
		int i = 0;
		for (NULL; i < size; i++) {
			if (strcmp(NAME, c[i])) {}

			else {
				*v = malloc(sizeof((i + 1) / 10 + 2));
				sprintf(*v, "%d", i + 1);
				
			}
		}
	}
	
}


#endif // !CASE_type_h
