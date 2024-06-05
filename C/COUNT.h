void COUNT(char*** PACK, int PACKSize, char**** rePACK, int* rePACKSize);

#ifndef COUNT_H
#define COUNT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "run.h"
#include "memory.h"
#include "CASE_type.h"
#include "mione.h"
#include "prerr.h"


void FunctionCall(char**FunctionAddress,char*** Pack,int PackSize,char * ***rePack,int * rePackSize) {
    printf("    HERE: FunctionCall\n");
    char *FucV = NULL;
    if (strcmp(FunctionAddress[0], "VALUE") == 0){
        FucV = memory[atoi(FunctionAddress[1])-1][1];
    }
    if (strcmp(FunctionAddress[0], "VARIABLE") == 0){
        FucV = memory[atoi(FunctionAddress[1])-1][2];
    }


    if (FucV == NULL) {
        prerr(0, "ERR", -1);
    }

    for (int i = 0; i < strlen(FucV); i++) {
        if (i) {
            if (i == strlen(FucV) - 1) {
                FucV[i - 1] = 0;
            }
            else {
                FucV[i - 1] = FucV[i];
            }
        }
    }



    for (int i = 0;i<PackSize;i++){
        if (i){
            if (i==PackSize-1){
                Pack[i-1] = NULL;
            }else{
                Pack[i-1] = Pack[i];
            }
        }
    }
    PackSize = PackSize-2;

    for (int i = 0;i<PackSize;i++){
        printf("to there : %s %s;",Pack[i][0],Pack[i][1]);
    }

    printf("OOOOOK : %s",FucV);

    char **Fuc = NULL;
    int Lines = 0;
    toBeCompileWithCode(FucV, &Fuc,&Lines);
    char***MIO=NULL;
    int c_size = compile(Fuc,Lines,&MIO);
    printf("cSize : %d\n",c_size);

    char ***FucReturn;
    int FucReturnSize = 0;

    char*** CountedWithV;
    int CountedWithVSize;
    COUNT(Pack,PackSize,&CountedWithV,&CountedWithVSize);
    run(&FucReturn,&FucReturnSize,c_size, CountedWithV, CountedWithVSize,MIO);

    *rePack = FucReturn;
    *rePackSize = FucReturnSize;
}

void toErrForCasesCount(char* reason,char * code,char***Pack) {
    static char* erPack[3];
    erPack[0] = "ERR";
    erPack[1] = reason;
    erPack[2] = code;
    *Pack = erPack;
}

void CasesCount(char***CASES,int CASESSize,char* ***rePack,int *rePackSize){
    //case()()
    //x()
    //y

    printf("    HERE: CasesCount\n");

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
        if (bracketLVL) {
            InBracketSize++;
            InBracket = realloc(InBracket, sizeof(char**) * InBracketSize);
            InBracket[InBracketSize - 1] = CASES[index];
        }
        else {
            if (strcmp(CASES[index][1], "7") == 0 && strcmp(CASES[index][0], "SYMBOL") == 0) {

            }
            else {
                PackSize++;
                Pack = realloc(Pack, sizeof(char**) * PackSize);
                Pack[PackSize - 1] = CASES[index];
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
                                char*** ReturnPACK;
                                int ReturnPACKSize;
                                FunctionCall(Pack[PackSize - 1], InBracket, InBracketSize,&ReturnPACK,&ReturnPACKSize);
                                Pack[PackSize - 1] = NULL;
                                PackSize--;

                                if (ReturnPACKSize){
                                    FucReIsVs[0] = PackSize-1;
                                    FucReIsVs[1] = ReturnPACKSize;
                                }

                                for (int i = 0; i < ReturnPACKSize; i++) {
                                    PackSize++;
                                    Pack[PackSize - 1] = ReturnPACK[i];
                                }

                                CASESSize = 0;
                                CASES = NULL;
                                CASES = malloc(0);

                                Pack = ReturnPACK;
                                PackSize = ReturnPACKSize;
                            }
                            else {
                                static char** err;
                                toErrForCasesCount("It is not a Function?", "1", &err);
                                *rePack =&err;
                                *rePackSize = 1;
                                return;
                            }
                        }
                    }
                }

                bracketType = 0; //end bracket
            }
        }
    }
    printf("Oh okay%d\n",*rePackSize);
    if (*rePackSize){
        if (strcmp(*rePack[0][0],"ERR")==0){

        }else{
            for (int i =0;i<*rePackSize;i++){
                char*value;
                char*type;
                to((*rePack)[i],&value,&type);
                (*rePack)[i][1] = value;
                (*rePack)[i][0] = type;
            }
        }
    }else{
        if (PackSize){
            *rePack = Pack;
            *rePackSize = PackSize;
        }else{
            static char a[] = "VALUE";
            static char b[] = "0";
            static char*  ni[] = {a,b};
            static char** nil[] = {ni};

            *rePack = nil;
            *rePackSize = 1;
        }

    }
}

void COUNT (char***PACK,int PACKSize,char * ***rePACK,int * rePACKSize){ //
    printf("    HERE: COUNT\n");

    char ***CASES = malloc(0); // a()
    int CASESSize = 0;

    char ***Pack = malloc(0); // 1 + a()
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
            printf("added case %s %s\n",CASES[CASESSize - 1][0],CASES[CASESSize - 1][1]);
        }


        if (strcmp(PACK[index][0], "SYMBOL") == 0) if (SYMBOL_CASE[atoi(PACK[index][1]) - 1].COUNT == 1) countCASE = 1;

        if (countCASE && ( lvl==0 || PACKSize-1 == index)) {


            char ***thatRerPack;
            int thatRerPackSize = 0;

            CasesCount(CASES, CASESSize, &thatRerPack,&thatRerPackSize);

            if (thatRerPackSize){
                if (strcmp(thatRerPack[thatRerPackSize - 1][0], "ERR")==0){

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
                    for (int ii =0;ii<thatRerPackSize;ii++){
                        printf("new\n");
                        PackSize++;
                        Pack = realloc(Pack, sizeof(char **) * (PackSize));
                        Pack[PackSize-1] = malloc(sizeof(char*)*2);

                        to(thatRerPack[ii],&(Pack[PackSize-1][0]),&(Pack[PackSize-1][1]));
                    }
                }





                CASES = NULL;
                CASES = malloc(0);
                CASESSize = 0;
            }else{
                //how?!!!
            }
        }

        if (strcmp(PACK[index][0], "SYMBOL") == 0)  if (strcmp(PACK[index][1], "8") == 0) lvl--;
    }

    for (int i = 0;i<PackSize;i++){
        char *ma;
        cm_v(&ma, atoi(Pack[i][1]),Pack[i][0]);
        Pack[i][0] = "VALUE";
        Pack[i][1] = ma;
    }

    *rePACK = Pack;
    *rePACKSize = PackSize;
    printf("    END: COUNT\n");
    return;
}

#endif