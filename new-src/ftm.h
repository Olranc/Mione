//File to Mione Objects

//
// Created by calle on 24-7-26.
//

#include "ttm.h"
mioObj* new(const char* fileName);

#ifndef FTM_H
#define FTM_H


mioObj* new(const char* fileName){
    FILE* f = fopen(fileName,"r");
    if (f==NULL)
    {
        fclose(f);
        return  NULL;
    }

    char* line = malloc(128);

    char **Mio=malloc(0);
    int MionSize=0;
    
    while (fgets(line,128,f))
    {
        MionSize++;
        Mio = realloc(Mio,sizeof(char*)*(MionSize));
        Mio[MionSize-1] = malloc(strlen(line)+1);
        strcpy(Mio[MionSize-1],line);


    }

    tts(Mio,MionSize);
    fclose(f);

}

#endif //FTM_H
