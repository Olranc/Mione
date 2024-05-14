//
// Created by chenn on 2024/4/11.
//
//M = mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
#ifndef MIONE_M_H
#define MIONE_M_H
#include "run.h"
#include <stdio.h>
#include "COUNT.h"
#include "prerr.h"
#include "run.h"


int V_V(char*** _while,int _whileSize,int firstI){
    printf("[NEW V/V]\n");
    int Index_ = firstI-1;

    char *** PACK = malloc(sizeof(char**)*1); //給V/V與Symbol用
    int PACKSize = 0;

    char* nowTargetType = 0; //0:HEAD

    int prompts = 0;

    for (int i = 0; i < _whileSize; i++) {
        char* TYPE = _while[i][0];
        if (strcmp(TYPE,"PROMPT") == 0){
            prompts++;
        }

    }

    for (int i = 0; i < _whileSize; i++) {
        Index_++;
        char* TYPE = _while[i][0];
        char* VALUE = _while[i][1];
        printf("    %s %s\n",_while[i][0],_while[i][1]);


        if ((strcmp(TYPE,"VALUE") == 0 || strcmp(TYPE,"SYMBOL") == 0 || strcmp(TYPE,"VARIABLE") == 0)){
            PACKSize++;
            PACK = realloc(PACK,sizeof(char**)*(PACKSize));
            PACK[PACKSize-1] = _while[i];
        }


        if (strcmp(TYPE,"PROMPT") == 0 || _whileSize-1 == i){
            if (nowTargetType == 0 && prompts) { //是HEAD
                PACKSize=0;
                free(PACK);
                PACK = malloc(sizeof(char**));
            }else{ //是 PROMPT
                char **** cP= COUNT(PACK,PACKSize);
                char *** countPack = *cP;

                PACKSize=0;
                free(PACK);
                PACK = malloc(sizeof(char**));

                printf("HERE RIGHT?\n");



                if (strcmp(countPack[0][0],"ERR") == 0){
                    int thisLine = 1;
                    for (int i = 0;i<NL;i++){
                        if (EveryLines[i]<=Index_){
                            thisLine = i+1; 
                        }else{
                            break;
                        }
                    }
                    printf("%s\n",countPack[0][2]);
                    prerr(thisLine,countPack[0][1],atoi(countPack[0][2]));
                }

                printf("passed VV");

            }
            char* lastTargetType = nowTargetType;
            nowTargetType = VALUE; //換到新的目標
        }


    }

    printf("[END V/V]\n\n");
}

//HEAD

int set(char*** _while,int _whileSize,int firstI) { //1
    printf("[NEW HEAD: SET]\n");
    char *** PACK = malloc(sizeof(char**)*1); //給V/V與Symbol用
    int PACKSize = 0;
    int Index_ = firstI-1;
    char* nowTargetType = 0; //0:HEAD

    for (int i = 0; i < _whileSize; i++) {
        Index_++;
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
        if (_whileSize-1 == i || (strcmp(TYPE,"PROMPT") == 0)){
            printf("HEY %d\n",strcmp(TYPE,"PROMPT"));
            if (i){
                if (nowTargetType == 0) { //是HEAD
                    PACKSize=0;
                    free(PACK);
                    PACK = malloc(sizeof(char**));
                }else{ //是 PROMPT
                    char **** cP= COUNT(PACK,PACKSize);
                    char *** countPack = *cP;

                    PACKSize=0;
                    free(PACK);
                    PACK = malloc(sizeof(char**));

                    //printf("HERE RIGHT?\n");
                    //printf("YES : %s\n",countPack[0][0]);



                    if (strcmp(countPack[0][0],"ERR") == 0){
                        int thisLine = 1;
                        for (int i = 0;i<NL;i++){
                            if (EveryLines[i]<=Index_){
                                thisLine = i+1;
                            }else{
                                break;
                            }
                        }
                        printf("%s\n",countPack[0][2]);
                        prerr(thisLine,countPack[0][1],atoi(countPack[0][2]));
                    }

                    printf("passed HEAD");
                }
            }

            char* lastTargetType = nowTargetType;
            nowTargetType = VALUE; //換到新的目標
        }


    }
    printf("[END HEAD: SET]\n\n");
}


#endif
