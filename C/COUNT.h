


#ifndef COUNT_H
#define COUNT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function ("Hello,"World!")

char*** COUNT (char***PACK,int PACKSize){ // { {"HELLO",<文字類性>},{"12346",<數字類性>},... }
    printf("        HERE:::\n");
    for (int index = 0;index<PACKSize;index++){
        printf("        %s %s\n",PACK[index][0],PACK[index][1]);
        if (strcmp(PACK[index][0],"VALUE")==0){

        }
    }
}

#endif