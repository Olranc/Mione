#ifndef COUNT_H
#define COUNT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "run.h"
#include "memory.h"
#include "CASE_type.h"


void FunctionCall(char*FunctionAdress,char*** Pack,int PacklSize,char * ***rePack,int * rePackSize) {

}

void toErrForCasesCount(char* reason,char * code,char***Pack) {
    static char* erPack[3];
    erPack[0] = "ERR";
    erPack[1] = reason;
    erPack[2] = code;
    *Pack = erPack;
}

void CasesCount(char***CASES,int CASESSize,char* **rePack){
    //case()()
    //x()
    //y

    printf("    HERE: CasesCount\n");
    printf("    Size is : %d\n", CASESSize);

    int bracketLVL = 0;
    int beforeBracket = 0;  //had to add 1 in this 

    int bracketType = 1;//0:Call Function 1:Choose Table Child

    char*** InBracket = malloc(0);
    int InBracketSize = 0;

    char*** Pack = malloc(0);
    int PackSize = 0;

    int FucReIsVs[]={
            0, //開始
            1 //長度
    };

    for (int index = 0;index<CASESSize;index++) {
        printf("        Index:%s %s\n",CASES[index][0],CASES[index][1]);
        if (bracketLVL) {
            InBracketSize++;
            InBracket = realloc(InBracket, sizeof(char**) * InBracketSize);
            InBracket[InBracketSize - 1] = CASES[index];
            printf("        ADDED\n");
        }
        else {
            if (strcmp(CASES[index][1], "7") == 0 && strcmp(CASES[index][0], "SYMBOL") == 0) {

            }
            else {
                PackSize++;
                Pack = realloc(Pack, sizeof(char**) * PackSize);
                Pack[PackSize - 1] = CASES[index];
                printf("        Pack Added\n");
            }
        }


        if (strcmp(CASES[index][0], "SYMBOL") == 0){
            if (strcmp(CASES[index][1], "7")==0){ // "("
                bracketType = 1;
                if (bracketLVL == 0) {
                    beforeBracket = index; //-1+1
                }
                if (bracketLVL) {}else {
                    InBracketSize++;
                    InBracket = realloc(InBracket, sizeof(char**) * InBracketSize);
                    InBracket[InBracketSize - 1] = CASES[index];
                    printf("        ADDED\n");
                }
                bracketLVL++;
            }
            if (strcmp(CASES[index][1], "8")==0){ // ")"
                bracketLVL--;

                if (bracketLVL) {}
                else {
                    if (bracketType == 1) { // Calling Function
                        if (strcmp(Pack[PackSize-1][0], "VALUE") == 0 || strcmp(Pack[PackSize - 1][0], "VARIABLE") == 0) {
                            int VVType = 0;//might be 4,Function
                            if (strcmp(Pack[PackSize - 1][0], "VALUE") == 0) {
                                VVType = atoi(memory[atoi(Pack[PackSize - 1][1])-1][0]);
                            }
                            if (strcmp(Pack[PackSize - 1][0], "VARIABLE") == 0) {
                                VVType = atoi(memory[atoi(Pack[PackSize - 1][1])-1][1]);
                            }

                            if (VVType == 4) {
                                char*** FunctionCalled;
                                int SIZE;
                                FunctionCall(Pack[PackSize - 1][1], InBracket, InBracketSize,&FunctionCalled,&SIZE);
                                Pack[PackSize - 1] = NULL;
                                PackSize--;

                                if (SIZE){
                                    FucReIsVs[0] = PackSize-1;
                                    FucReIsVs[1] = SIZE;
                                }

                                for (int i = 0; i < SIZE; i++) {
                                    PackSize++;
                                    Pack[PackSize - 1] = FunctionCalled[i];
                                }

                                CASESSize = 0;
                                CASES = NULL;
                                CASES = malloc(0);
                            }
                            else {
                                static char** err;
                                toErrForCasesCount("It is not a Function?", "1", &err);
                                *rePack = err;
                                return;
                            }
                        }
                    }
                }

                bracketType = 0; //end bracket
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

    int lvl = 0;

    for (int index = 0;index<PACKSize;index++) {
        int addCASE = 0;
        int countCASE = 0;

        if (PACKSize-1 == index) {countCASE = 1,addCASE = 1;};

        if (strcmp(PACK[index][0], "SYMBOL") == 0)  if (strcmp(PACK[index][1], "7") == 0) lvl++;
       

        if (strcmp(PACK[index][0], "VALUE") == 0 || strcmp(PACK[index][0], "VARIABLE") == 0) addCASE = 1;
        if (strcmp(PACK[index][0], "SYMBOL") == 0) if (SYMBOL_CASE[atoi(PACK[index][1]) - 1].COUNT == 0) addCASE = 1;

        if (addCASE || lvl) {
            CASESSize++;
            CASES = realloc(CASES, sizeof(char **) * (CASESSize));
            CASES[CASESSize - 1] = PACK[index];
        }


        if (strcmp(PACK[index][0], "SYMBOL") == 0) if (SYMBOL_CASE[atoi(PACK[index][1]) - 1].COUNT == 1) countCASE = 1;
        printf("    ITEM : %s %s a:%d c:%d %d\n", PACK[index][0], PACK[index][1],addCASE,countCASE, lvl);

        if (countCASE && ( lvl==0 || PACKSize-1 == index)) {
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

        if (strcmp(PACK[index][0], "SYMBOL") == 0)  if (strcmp(PACK[index][1], "8") == 0) lvl--;
    }

    printf("    size is : %d\n", PackSize);

    *rePACK = Pack;
    *rePACKSize = PackSize;
    printf("    END: COUNT\n");
    return;
}

#endif