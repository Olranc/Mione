#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "HEAD.h"
#include "VV.h"

#ifndef CASE_type_h
#define CASE_type_h

typedef  struct   {
    char* NAME;
    int (*fuc)(char***,int);
} THECASE;

typedef  struct   {
    char* ID;
    int ForHead;
} THEPCASE;

THECASE HEAD_CASE[] = { //how? ";" didnt here ,and it works??? // oh nvm
        {"1",NULL},
        {"2",set},
};

THEPCASE P_CASE[] = {
        {"1",1},
        {"2",1},
        {"3",1},
        {"4",1},
        {"5",0},
};
char* HEADS[] = {
        "input",
        "set",
        ";"
};




char* PROMOTS[] = {
	"do",
	"then",
	"else",
	"=",
    "=>"
};



char* SYMBOLS[] = {
	"==",
	"-",
	"+",
	"^",
	"*",
	"/",
	"(",
	")",
    ","
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
