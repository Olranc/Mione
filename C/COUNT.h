#ifndef COUNT_H
#define COUNT_H

int COUNT (char***PACK,int PACKSize){
    printf("        HERE:::\n");
    for (int index = 0;index<PACKSize;index++){
        printf("        %s %s\n",PACK[index][0],PACK[index][1]);
    }
}

#endif