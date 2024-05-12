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
                printf("OFF %d\n",lvl);


                COUNT(Pack,PackSize);
                Pack = NULL;
                PackSize = 0;
            }
        }
    }
    printf("\n");
}

#endif