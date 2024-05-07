#ifndef CASE_type_h
#define CASE_type_h


typedef  struct   {
    char* NAME;
    int (*fuc)(char***,int);
} THE_HEAD_CASE;

typedef  struct   {
    char* NAME;
    int VV;
} THE_SYMBOL_CASE;

char* PROMPTS[];

THE_HEAD_CASE HEAD_CASE[];
THE_SYMBOL_CASE SYMBOL_CASE[];

#include "M.h"




char* HEADS[] = {
        "input",
        "set",
        ";"
};
THE_HEAD_CASE HEAD_CASE[] = {
        {"1",NULL},
        {"2",set},
};

THE_SYMBOL_CASE SYMBOL_CASE[] = {
        {"1",1},
        {"2",1},
        {"3",1},
        {"4",1},
        {"5",1},
        {"6",1},
        {"7",1},
        {"8",0},
        {"9",1},
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
        ",",
        "[",
        "]"
};

char* PROMPTS[] = {
	"do",
	"then",
	"else",
    "as",
	"=",
    "=>"
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
