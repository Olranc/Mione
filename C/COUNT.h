#ifndef COUNT_H
#define COUNT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function ("Hello,"World!")

char*** COUNT (char***PACK,int PACKSize){ // { {"HELLO",<文字類性>},{"12346",<數字類性>},... }
    printf("      HERE:::\n");
    int lvl = 0;

    char ***Pack = malloc(sizeof(char**));
    int PackSize = 0;
    int lastCaseNumOutLvl = 0;

    for (int index = 0;index<PACKSize;index++){
        printf("        %s %s\n",PACK[index][0],PACK[index][1]);

        if (strcmp(PACK[index][0],"VALUE")==0 || strcmp(PACK[index][0],"VARIABLE")==0){
            if (lvl){
                PackSize++;
                Pack = realloc(Pack,PackSize*sizeof(char**));
                Pack[PackSize-1] = PACK[index];
            }else{
                lastCaseNumOutLvl = index;
                printf("%d\n",lastCaseNumOutLvl);
            }
        }
        if (strcmp(PACK[index][0],"SYMBOL")==0){
            if (strcmp(PACK[index][1],"7")==0){
                lvl++;

                PackSize++;
                Pack = realloc(Pack,PackSize*sizeof(char**));
                Pack[PackSize-1] = PACK[index];
            }
            if (strcmp(PACK[index][1],"8")==0){
                lvl--;

                PackSize++;
                Pack = realloc(Pack,PackSize*sizeof(char**));
                Pack[PackSize-1] = PACK[index];


            }
        }
    }
}

#endif