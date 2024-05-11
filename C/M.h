//
// Created by chenn on 2024/4/11.
//
//M = mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
#ifndef MIONE_M_H
#define MIONE_M_H
#include "run.h"
#include <stdio.h>
#include "COUNT.h"


int V_V(char*** _while,int _whileSize){
    printf("[NEW V/V]\n");

    char *** PACK = malloc(sizeof(char**)*1); //給V/V與Symbol用
    int PACKSize = 0;

    char* nowTargetType = 0; //0:HEAD

    for (int i = 0; i < _whileSize; i++) {

        char* TYPE = _while[i][0];
        char* VALUE = _while[i][1];
        printf("    %s %s\n",_while[i][0],_while[i][1]);


        if ((strcmp(TYPE,"VALUE") == 0 || strcmp(TYPE,"SYMBOL") == 0 || strcmp(TYPE,"VARIABLE") == 0)){
            PACKSize++;
            PACK = realloc(PACK,sizeof(char**)*(PACKSize));
            PACK[PACKSize-1] = _while[i];
        }

        if (_whileSize-1 == i){
            COUNT(PACK,PACKSize);


            PACKSize=0;
            free(PACK);
            PACK = malloc(sizeof(char**));

        }

        if (strcmp(TYPE,"PROMPT") == 0){
            if (nowTargetType == 0) { //是HEAD
                PACKSize=0;
                free(PACK);
                PACK = malloc(sizeof(char**));
            }else{ //是 PROMPT
                COUNT(PACK,PACKSize);

                PACKSize=0;
                free(PACK);
                PACK = malloc(sizeof(char**));
            }
            char* lastTargetType = nowTargetType;
            nowTargetType = VALUE; //換到新的目標
        }


    }

    printf("[END V/V]\n\n");
}

//HEAD

int set(char*** _while,int _whileSize) { //1
    printf("[NEW HEAD: SET]\n");
    char *** PACK = malloc(sizeof(char**)*1); //給V/V與Symbol用
    int PACKSize = 0;

    char* nowTargetType = 0; //0:HEAD

    for (int i = 0; i < _whileSize; i++) {
        char* TYPE = _while[i][0];
        char* VALUE = _while[i][1];



        if (i){
            if ((strcmp(TYPE,"VALUE") == 0 || strcmp(TYPE,"SYMBOL") == 0 || strcmp(TYPE,"VARIABLE") == 0)){
                printf("    %s %s\n",_while[i][0],_while[i][1]);
                PACKSize++;
                PACK = realloc(PACK,sizeof(char**)*(PACKSize));
                PACK[PACKSize-1] = _while[i];
            }
        }
        if (PACKSize&&(_whileSize-1 == i || (strcmp(TYPE,"PROMPT") == 0))){
            char* lastTargetType = nowTargetType;
            nowTargetType = VALUE; //換到新的目標

            COUNT(PACK,PACKSize);

            PACKSize=0;
            free(PACK);
            PACK = malloc(sizeof(char**));
        }


    }
    printf("[END HEAD: SET]\n\n");
}


#endif //MIONE_M_H
