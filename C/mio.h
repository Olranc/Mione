


#ifndef mio_h
#define mio_h
#include "run.h"
#include "memory.h"


int pass = 0;

int mioEnd(){
    NL++;
    if (EveryLines) {
        EveryLines = realloc(EveryLines, sizeof(int) * NL);
    }
    else {
        EveryLines = malloc(sizeof(int) * 1);
    }
    //printf("new line %d\n",NL);
    EveryLines[NL - 1] = cSize;
}

// set							x								=								"hello"
// <HEAD ID>    <虛擬記憶體位置>     <記憶體位置>		<虛擬記憶體位置>

// "a"=="a"
// <虛擬記憶體位置> <符號ID> <虛擬記憶體位置>

int setC(char* _type, char* _case, int _t) {
    cSize++;
    if (MIO  ) {
        MIO   = realloc(MIO  , cSize * sizeof(char**));
    }
    else {
        MIO   = malloc(sizeof(char**));
    }

    MIO  [cSize - 1] = malloc(sizeof(char*)*2);


    MIO  [cSize - 1][0] = malloc(strlen(_type)+1);
    strcpy(MIO  [cSize - 1][0], _type);


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





    MIO  [cSize - 1][1] = malloc(strlen(_case)+1);
    strcpy(MIO  [cSize - 1][1], _case);

    printf("A:%s %s\n", MIO  [cSize - 1][1],MIO  [cSize - 1][0]);
    pass = 1;

    return 1;
}

int mio(char* _case, int _type) { // HEAD,PROMPT,VALUE,VARIABLE,SYMBOL

	//HEAD:HEAD_NAME

	printf("[CASE]:`%s`				[TYPE]:`%d` \n", _case, _type);
	pass = 0;

	for (int i = 0; i < sizeof(HEADS) / sizeof(char*); i = i + 1) {

		if (strcmp(HEADS[i], _case)) {
		}
		else {
			setC("HEAD", _case, _type);
		}
	}

	if (pass) {}else{
		for (int i = 0; i < sizeof(PROMPTS) / sizeof(char*); i = i + 1) {

			if (strcmp(PROMPTS[i], _case)) {
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

    for (int i = 0;i<strlen(_case);i++){
        if (_case[i] == '\n') mioEnd();
    }


    return 1;
}



#endif