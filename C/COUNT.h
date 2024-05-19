#ifndef COUNT_H
#define COUNT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "run.h"
#include "memory.h"
#include "CASE_type.h"

void toErrForCasesCount(char* reason,char * code,char***Pack) {
    static char* erPack[3];
    erPack[0] = "ERR";
    erPack[1] = reason;
    erPack[2] = code;
    *Pack = erPack;
}

void CasesCount(char***CASES,int CASESSize,char* **rePack){

    printf("    HERE: CasesCount\n");

    int bracketLVL = 0;
    int beforeBracket = 0;  //had to add 1 in this 

    for (int index = 0;index<CASESSize;index++) {
        printf("        CC : %s %s\n", CASES[index][0], CASES[index][1]);
        printf("        D:%d\n",beforeBracket-1);

        if (beforeBracket&&beforeBracket-1>=0) {
            if (strcmp(CASES[beforeBracket-1][0], "VALUE")==0||strcmp(CASES[beforeBracket-1][0], "VARIABLE")==0){
                printf("        start by: %s %s\n", CASES[index][0], CASES[index][1]);
                int BBType = 0; //Before Bracket Type

                if (strcmp(CASES[beforeBracket-1][0], "VALUE")==0) BBType=atoi(memory[atoi(CASES[beforeBracket-1][1])-1][0]);
                if (strcmp(CASES[beforeBracket-1][0], "VARIABLE")==0) BBType=atoi(memory[atoi(CASES[beforeBracket-1][1])-1][1]);

                printf("        Before Bracket Type: %d\n", BBType);
                if (BBType == 4){
                    printf("        ok it is a function call\n");
                }else {
                    static char** erPack;
                    toErrForCasesCount("It is not a Function,Can't to function call.", "1", &erPack);
                    *rePack = erPack;
                    printf("    !!!Found an ERROR by CasesCount\n");
                    return;
                }
            }
        }

        if (strcmp(CASES[index][0], "SYMBOL") == 0){
            if (strcmp(CASES[index][1], "7")==0){ // "("
                if (bracketLVL == 0) {
                    beforeBracket = index; //-1+1
                }
                bracketLVL++;
            }
            if (strcmp(CASES[index][1], "8")==0){ // ")"
                bracketLVL--;
                if (bracketLVL == 0) {
                    beforeBracket = 1; //-1+1
                }
            }
        }
    }

    static char a[]= "NUMBER";
    static char w[]= "7";

    static char *aw[] = {a,w};

    *rePack = aw;
}

void COUNT (char***PACK,int PACKSize,char * ***rePACK,int * rePACKSize){ //
    printf("    HERE: COUNT\n");

    char ***CASES = malloc(0);

    int CASESSize = 0;

    char ***Pack = malloc(0);
    int PackSize = 0;

    for (int index = 0;index<PACKSize;index++) {
        int addCASE = 0;
        int countCASE = 0;



        if (PACKSize-1 == index) {countCASE = 1,addCASE = 1;};

        if (strcmp(PACK[index][0], "VALUE") == 0 || strcmp(PACK[index][0], "VALUE") == 0) addCASE = 1;
        if (strcmp(PACK[index][0], "SYMBOL") == 0) if (SYMBOL_CASE[atoi(PACK[index][1]) - 1].COUNT == 0) addCASE = 1;

        if (addCASE) {
            CASESSize++;
            CASES = realloc(CASES, sizeof(char **) * (CASESSize));
            CASES[CASESSize - 1] = PACK[index];
        }


        if (strcmp(PACK[index][0], "SYMBOL") == 0) if (SYMBOL_CASE[atoi(PACK[index][1]) - 1].COUNT == 1) countCASE = 1;
        printf("    ITEM : %s %s a:%d c:%d\n", PACK[index][0], PACK[index][1],addCASE,countCASE);

        if (countCASE) {
            PackSize++;
            Pack = realloc(Pack, sizeof(char **) * (PackSize));
            CasesCount(CASES, CASESSize, &(Pack[PackSize - 1]));

            if (strcmp(Pack[PackSize - 1][0], "ERR")==0){
                printf("    !!!Caught an ERROR from CasesCount\n");
                static char *errPack[3];
                errPack[0] = Pack[PackSize - 1][0];
                errPack[1] = Pack[PackSize - 1][1];
                errPack[2] = Pack[PackSize - 1][2];
                static char **erPack[] = {errPack};
                *rePACK = erPack;
                *rePACKSize = 1;
                return;
            }else{
                //可以外方
            }
            printf("    OKAY IT IS: %s\n", Pack[PackSize - 1][0]);

            CASES = realloc(CASES, 0);
            CASESSize = 0;
        }
    }

    printf("    size is : %d\n", PackSize);

    *rePACK = Pack;
    *rePACKSize = PackSize;
    printf("    END: COUNT\n");
    return;
}

#endif