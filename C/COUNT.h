#ifndef COUNT_H
#define COUNT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "memory.h"

int PackSize = 0;
// Function ("Hello,"World!")
int getSize(){
    return PackSize;
}

char**** COUNT (char***PACK,int PACKSize){ // { {"HELLO",<文字類性>},{"12346",<數字類性>},... }
    printf("      HERE:::\n");
    int lvl = 0;

    int lastCaseNumOutLvl = 0;

    char ****tobeCount = malloc(sizeof(char***));
    *tobeCount = malloc(sizeof(char**));
    int inSideTobeCountSize = 0;
    int countTarget = 0;

    int canDoSecond = 1;

    int bracketStartInPlusOne = 0;

    for (int index = 0;index<PACKSize;index++){
        if (strcmp(PACK[index][0],"SYMBOL")==0){
           if (strcmp(PACK[index][1],"7")==0){ //(
               canDoSecond = 0;
           }
            if (strcmp(PACK[index][1],"5")==0){ //*
                canDoSecond = 0;
            }
            if (strcmp(PACK[index][1],"6")==0){ // /
                canDoSecond = 0;
            }
        }
    }


    for (int index = 0;index<PACKSize;index++){
        printf("        %s %s %d\n",PACK[index][0],PACK[index][1],PACKSize);

        if (strcmp(PACK[index][0],"SYMBOL")==0){
            if (strcmp(PACK[index][1],"7")==0){
                if (lvl){}else{
                    bracketStartInPlusOne = index+1;
                    printf("BRACKET START IN %d\n",bracketStartInPlusOne);
                }
                lvl++;
            }
            if (strcmp(PACK[index][1],"8")==0){

                lvl--;
            }
        }

        if (strcmp(PACK[index][0],"VALUE")==0 || strcmp(PACK[index][0],"VARIABLE")==0){
            if (canDoSecond){

            }else{
                if (lvl){
                }else{
                    printf("ME %s %s\n",PACK[index][0],PACK[index][1]);
                    lastCaseNumOutLvl = index;
                    //printf("%d\n",lastCaseNumOutLvl);


                }
                inSideTobeCountSize++;
                tobeCount[countTarget] = realloc(tobeCount[countTarget],inSideTobeCountSize*sizeof(char**));
                tobeCount[countTarget][inSideTobeCountSize-1] = PACK[index];
            }


        }

        if (bracketStartInPlusOne){
            int bracketStartIn = bracketStartInPlusOne -1;
            for (int In = bracketStartIn;In<PACKSize;In++){
                printf("HEHEHEHEHEHEHEHE : %s %s \n",PACK[In][0],PACK[In][1]);
            }
            bracketStartInPlusOne = 0;
        }
        printf("\n");
    }

    char ***Pack = malloc(sizeof(char***));


    if (PackSize == 0){
        PackSize++;

        static char* AW1[] = {"VALUE","0"};
        static char **AW2[] = {AW1};
        static char ***AW[] = {AW2};

        Pack = *AW;
    }

    printf("-------------\n");
    for (int i = 0;i<PackSize;i++){
        printf("%s %s\n",Pack[i][0],Pack[i][1]);
    }
    printf("-------------\n");

    char ****returnPack = malloc(sizeof(char****));
    *returnPack = Pack;
    return returnPack;

}

#endif