#ifndef COUNT_H
#define COUNT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "run.h"
#include "memory.h"
#include "CASE_type.h"

int returnPackSize = 0;
// Function ("Hello,"World!")
int getSize(){
    return returnPackSize;
}

char *** CasesCount(char***CASES,int CASESSize){
    static char a[] = "NUMBER";
    static char b[] = "2";
    static char *ab[2]  ;
    ab[0] = a;
    ab[1] = b;
    static char **fin[] = {ab};
    return fin; //先這樣
}

char**** COUNT (char***PACK,int PACKSize){ // { {"HELLO",<文字類性>},{"12346",<數字類性>},... }

    printf("      HERE:::\n");
    //printf("%s %s\n", CasesCount(NULL,0)[0][0],CasesCount(NULL,0)[0][1]);

    int canDo = 1;

    char ****Pack = malloc(sizeof(char***)*1);
    int PackTarget = 0;
    int* PackSize = malloc(sizeof(int)*1);


    PackSize[PackTarget] = 0;


    char ***CASES = malloc(sizeof(char**)*0);
    int CASESSize = 0;

    int nowCOUNTing = 0;

    for (int index = 0;index<PACKSize;index++){
        if (strcmp(PACK[index][0],"SYMBOL")==0){
            if (strcmp(PACK[index][1],"5")==0){ //*
                canDo = 2;
            }
        }
    }


    for (int index = 0;index<PACKSize;index++){
        int doCount = 0;
        if (PACKSize - 1 == index) doCount = 1;
        if (strcmp(PACK[index][0], "SYMBOL") == 0) if (SYMBOL_CASE[atoi(PACK[index][1]) - 1].COUNT) doCount = 1;

        if (doCount) {

            //printf("COUNT %d \n",PackSize[PackTarget]);
            if (PackSize[PackTarget]) {
                PackSize[PackTarget]++;
                //printf("change memory for pack %d\n", PackSize[PackTarget]);
                Pack[PackTarget] = realloc(Pack[PackTarget], sizeof(char**) * PackSize[PackTarget]);
                //printf("changed\n");
            }
            else {
                PackSize[PackTarget]++;
                //printf("add memory for pack %d\n", PackSize[PackTarget]);
                Pack[PackTarget] = malloc(sizeof(char**) * PackSize[PackTarget]);
                //printf("added\n");
            }

            Pack[PackTarget][PackSize[PackTarget] - 1] = CasesCount(CASES, CASESSize)[0];

            CASES = NULL;
            CASES = malloc(sizeof(char**) * 1);
            CASESSize = 0;


            if (nowCOUNTing == 5) {
                if (PackSize[PackTarget] >= 2) {

                }
                else {
                    static char TYP[] = "ERR";
                    static char MSG[] = "Too short.";

                    static char* ERR[2];
                    ERR[0] = TYP;
                    ERR[1] = MSG;

                    static char** ERR_PACK[] = { ERR };
                    static char*** ERR_PACKS[] = { ERR_PACK };

                    return ERR_PACKS;
                }

                printf("okokok %s %d\n", Pack[PackTarget][1][0], PackSize[PackTarget]);

                char** New = Pack[PackTarget][PackSize[PackTarget] - 1];
                printf("NEW ADDED\n");
                char** Last = Pack[PackTarget][PackSize[PackTarget] - 2]; //todo SHIT
                printf("LAST ADDED\n");




                if (strcmp(Last[0], "NUMBER") == 0 && strcmp(New[0], "NUMBER") == 0) {

                    printf("%d\n", atoi(Last[1]) * atoi(New[1]));
                }
                else {
                    static char TYP[] = "ERR";
                    static char MSG[] = "Can't count this type of VALUE or VARIABLE.";

                    static char* ERR[2];
                    ERR[0] = TYP;
                    ERR[1] = MSG;

                    static char** ERR_PACK[] = { ERR };
                    static char*** ERR_PACKS[] = { ERR_PACK };

                    return ERR_PACKS;
                }
            }
            else {
                printf("NEXT TO DO\n");
            }

            nowCOUNTing = 0;
        }

        if (strcmp(PACK[index][0], "VARIABLE") == 0 || strcmp(PACK[index][0], "VALUE") == 0) {
            if (nowCOUNTing) {

            }
            else {

                CASESSize++;
                CASES = realloc(CASES, sizeof(char**) * CASESSize); \
                    CASES[CASESSize - 1] = PACK[index];
            }
        }

        if (canDo==1) {
            // , + -
        }else if (canDo == 2){   

            if (strcmp(PACK[index][0],"SYMBOL")==0){
                if (SYMBOL_CASE[atoi(PACK[index][1])-1].COUNT==0){
                    CASESSize ++;
                    CASES = realloc(CASES, sizeof(char**)*CASESSize);
                    CASES[CASESSize-1] = PACK[index];
                }else{

                }


                if (strcmp(PACK[index][1],"5")==0) {
                    nowCOUNTing = 5;
                }


                if (strcmp(PACK[index][1], "2") == 0) {
                    CASESSize++;
                    CASES = realloc(CASES, sizeof(char**) * CASESSize);
                    CASES[CASESSize - 1] = PACK[index];
                }

                if (strcmp(PACK[index][1], "3") == 0) {
                    CASESSize++;
                    CASES = realloc(CASES, sizeof(char**) * CASESSize);
                    CASES[CASESSize - 1] = PACK[index];
                }
            }
        }
    }
    static char TYP[] = "GOOD";
    static char MSG[] = "GOOD";

    static char *ERR[2];
    ERR[0] = TYP;
    ERR[1] = MSG;

    static char **ERR_PACK[] = {ERR};
    static char ***ERR_PACKS[] = {ERR_PACK};

    return ERR_PACKS;


}

#endif