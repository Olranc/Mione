#ifndef CASE_type_h
#define CASE_type_h


typedef  struct   {
    char* NAME;
    int (*fuc)(char***,int);
} THECASE;
char* PROMPTS[];

THECASE HEAD_CASE[];

#include "M.h"




char* HEADS[] = {
        "input",
        "set",
        ";"
};
THECASE HEAD_CASE[] = { //how? ";" didnt here ,and it works??? // oh nvm
        {"1",NULL},
        {"2",set},
};


char* PROMPTS[] = { //我知道我英文不好
	"do",
	"then",
	"else",
    "as",
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
	char** c = (strcmp(_type, "HEAD") ? (strcmp(_type, "PROMPT") ? (strcmp(_type, "SYMBOL") ? NULL : SYMBOLS) : PROMPTS) : HEADS);

	int size = (strcmp(_type, "HEAD") ? (strcmp(_type, "PROMPT") ? (strcmp(_type, "SYMBOL") ? 0 : sizeof(SYMBOLS)) : sizeof(PROMPTS)) : sizeof(HEADS))/sizeof(char*);
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
