#ifndef COUNT_H
#define COUNT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "memory.h"

// Function ("Hello,"World!")

char**** COUNT (char***PACK,int PACKSize){ // { {"HELLO",<文字類性>},{"12346",<數字類性>},... }
    printf("      HERE:::\n");
    int lvl = 0;

    char ***Pack = malloc(sizeof(char**));
    int PackSize = 0;
    int lastCaseNumOutLvl = 0;

    char ***rePack = malloc(sizeof(char**));
    int rePackSize = 0;

    for (int index = 0;index<PACKSize;index++){
        printf("        %s %s %d\n",PACK[index][0],PACK[index][1],PACKSize);

        if (strcmp(PACK[index][0],"VALUE")==0 || strcmp(PACK[index][0],"VARIABLE")==0){
            if (lvl){
                PackSize++;
                Pack = realloc(Pack,PackSize*sizeof(char**));
                Pack[PackSize-1] = PACK[index];
            }else{
                lastCaseNumOutLvl = index;
                //printf("%d\n",lastCaseNumOutLvl);
            }
        }
        if (strcmp(PACK[index][0],"SYMBOL")==0){
            if (strcmp(PACK[index][1],"7")==0){

                lvl++;

                if (lvl == 1){

                }else{
                    PackSize++;
                    Pack = realloc(Pack,PackSize*sizeof(char**));
                    Pack[PackSize-1] = PACK[index];
                }


            }
            if (strcmp(PACK[index][1],"8")==0){
                lvl--;

                if (lvl == 0){

                }else{
                    PackSize++;
                    Pack = realloc(Pack,PackSize*sizeof(char**));
                    Pack[PackSize-1] = PACK[index];
                }






                for (int i = 0;i<PackSize;i++){
                    printf("            TO: %s %s\n",Pack[i][0],Pack[i][1]);
                }
                //printf("OFF %d\n",lvl);


                if (strcmp(PACK[lastCaseNumOutLvl][0],"VALUE") == 0 || strcmp(PACK[lastCaseNumOutLvl][0],"VARIABLE") == 0) {
                    if(strcmp(memory[atoi(PACK[lastCaseNumOutLvl][1])-1][0],"4") == 0){
                        printf("calling function\n");
                    }else{

                        static char _TYPE[] = "ERR";
                        static char _MSG[] = "Oh it is not a function.";
                        static char _LINE[] = "1";

                        static char* erPack1[] = {_TYPE,_MSG,_LINE};
                        static char **erPack2[] = {erPack1};
                        static char ***erPack[] = {erPack2};

                        printf("YES ERROR\n");
                        return erPack;
                    }
                }

                Pack = NULL;
                PackSize = 0;
            }
        }
        printf("\n");
    }

    if (rePackSize == 0){

        rePackSize++;

        static char* AW1[] = {"VALUE","0"};
        static char **AW2[] = {AW1};
        static char ***AW[] = {AW2};

        rePack = *AW;
    }

    printf("-------------\n");
    for (int i = 0;i<rePackSize;i++){
        printf("%s %s\n",rePack[i][0],rePack[i][1]);
    }
    printf("-------------\n");

    char ****returnPack = malloc(sizeof(char****));
    *returnPack = rePack;
    return returnPack;

}

#endif