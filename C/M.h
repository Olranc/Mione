//
// Created by chenn on 2024/4/11.
//
//M = mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
#ifndef MIONE_M_H
#define MIONE_M_H
#include "run.h"
#include <stdio.h>

int V_V(char*** _while,int _whileSize){
    printf("[NEW V/V]\n");

    for (int i = 0; i < _whileSize; i++) {
        printf("    %s %s\n",_while[i][0],_while[i][1]);
    }
    printf("[END V/V]\n\n");
}

//HEAD

int set(char*** _while,int _whileSize) { //1
    printf("[NEW HEAD]\n");
    char *** PACK = malloc(sizeof(char**)*1);

    for (int i = 0; i < _whileSize; i++) {
        char* TYPE = _while[i][0];
        char* VALUE = _while[i][1];
        printf("    %s %s\n",_while[i][0],_while[i][1]);



        if (strcmp(TYPE,"SYMBOL")){}else{
            if (strcmp(VALUE,"9")){}else{
                    printf("ok");
            }
        }
    }
    printf("[END HEAD]\n\n");
}


#endif //MIONE_M_H
