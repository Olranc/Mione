#include <stdio.h>
#include <string.h>
#include <stdlib.h>



#ifndef HEAD_h
#define HEAD_h



int set(char*** _while,int _whileSize) { //1
    printf("    [NEW HEAD]\n");
    for (int i = 0; i < _whileSize; i++) {
        printf("%s %s\n",_while[i][0],_while[i][1]);

    }
    printf("    [END HEAD]\n\n");
}



#endif 
