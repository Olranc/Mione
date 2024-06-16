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


void V_V(char*** _while,int _whileSize,int firstI,int* OPSize,char* *** OUTPUT,char *** fucIn,int fucInSize,int MEMORY_GROUP,int NL,int* EveryLines ){
    printf("        [NEW V/V]\n");
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
                char *** countPack;
                int countPackSize;
                COUNT(PACK,PACKSize,&countPack,&countPackSize,MEMORY_GROUP);

                PACKSize=0;
                free(PACK);
                PACK = malloc(sizeof(char**));

                if (strcmp(countPack[0][0],"ERR") == 0){

                    int thisLine = 1;
                    for (int i = 0;i<NL;i++){

                        thisLine = i+1;
                        if (EveryLines[i]<Index_){

                        }else{
                            break;
                        }
                    }

                    prerr(thisLine,countPack[0][1],atoi(countPack[0][2]));

                    //char Line[12];
                    //sprintf(Line, "%d", (thisLine) + thisLine);

                    //char ***Err = malloc(sizeof(char**));
                    //Err[0] = malloc(sizeof(char*)*4);
                    //Err[0][0] = "ERR";
                    //Err[0][1] = countPack[0][2];
                    //Err[0][2] = countPack[0][1];
                    //Err[0][3] = "1";
                    //*OUTPUT = Err;

                    //return;
                }

            }
            char* lastTargetType = nowTargetType;
            nowTargetType = VALUE; //換到新的目標
        }


    }

    printf("        [END V/V]\n\n");
}

//HEAD

void set(char*** _while,int _whileSize,int firstI,int* OPSize,char* *** OUTPUT,char *** fucIn,int fucInSize,int MEMORY_GROUP,int NL,int* EveryLines ) { //1
    printf("        [NEW HEAD: SET]\n");
    char *** PACK = malloc(sizeof(char**)*1); //給V/V與Symbol用
    int PACKSize = 0;
    int Index_ = firstI-1;
    char* nowTargetType = 0; //0:HEAD

    for (int i = 0; i < _whileSize; i++) {
        Index_++;
        char* TYPE = _while[i][0];
        char* VALUE = _while[i][1];
        printf("            [ITME] : '%s' '%s'\n",TYPE,VALUE);



        if ((strcmp(TYPE,"VALUE") == 0 || strcmp(TYPE,"SYMBOL") == 0 || strcmp(TYPE,"VARIABLE") == 0)){
            PACKSize++;
            PACK = realloc(PACK,sizeof(char**)*(PACKSize));
            PACK[PACKSize-1] = _while[i];
        }
        if (_whileSize-1 == i || (strcmp(TYPE,"PROMPT") == 0)){
            if (nowTargetType == 0) { //是HEAD 重要！！！
                PACKSize=0;
                free(PACK);
                PACK = malloc(sizeof(char**));
            }else{ //是 PROMPT
                char *** countPack;
                int countPackSize;
                COUNT(PACK,PACKSize,&countPack,&countPackSize,MEMORY_GROUP);
                printf("end?\n");

                PACKSize=0;
                free(PACK);
                PACK = malloc(sizeof(char**));

                if (strcmp(countPack[0][0],"ERR") == 0){
                    int thisLine = 1;
                    int lastLine =0;

                    int vindex=-1;
                    printf("nnn %d\n",Index_);
                    for (int i = 0; i < NL; i++) {



                        thisLine = i+1;
                        if (EveryLines[i] < Index_) {

                        } else {
                            break;
                        }
                        if (vindex == EveryLines[i]){}else{
                            lastLine = i+1;
                            vindex=EveryLines[i];
                        }

                    }


                    char ***Err = malloc(sizeof(char**));
                    Err[0] = malloc(sizeof(char*)*5);
                    Err[0][0] = "ERR";
                    Err[0][1] = countPack[0][1];

                    for (int i = 0; i < 5; i++) {
                        printf("pack %s\n",countPack[0][i]);
                    }
                    Err[0][2] = countPack[0][2];
                    Err[0][3] = malloc(12);
                    if (countPack[0][3]==NULL){
                        sprintf( Err[0][3], "%d", thisLine);

                    }else{
                        sprintf( Err[0][3], "%d", thisLine-atoi(countPack[0][4])+ atoi(countPack[0][3]));

                    }
                    Err[0][4] = malloc(12);
                    sprintf(Err[0][4], "%d",NL-1);
                    *OUTPUT = Err;
                    *OPSize = 1;

                    return;
                }else{
                    //一定會用到這裡
                }
            }

            char* lastTargetType = nowTargetType;
            nowTargetType = VALUE; //換到新的目標
        }


    }
    printf("        [END HEAD: SET]\n\n");
}

void return_(char*** _while,int _whileSize,int firstI,int* OPSize,char* *** OUTPUT,char *** fucIn,int fucInSize,int MEMORY_GROUP,int NL,int* EveryLines ){
    printf("        [NEW HEAD: RETURN]\n");
    char *** PACK = malloc(sizeof(char**)*1); //給V/V與Symbol用
    int PACKSize = 0;
    int Index_ = firstI-1;
    char* nowTargetType = 0; //0:HEAD

    for (int i = 0; i < _whileSize; i++) {
        printf("            [FUCK] : '%s' '%s'\n",_while[i][0],_while[i][1]);
        Index_++;
        char *TYPE = _while[i][0];
        char *VALUE = _while[i][1];


        if ((strcmp(TYPE, "VALUE") == 0 || strcmp(TYPE, "SYMBOL") == 0 || strcmp(TYPE, "VARIABLE") == 0)) {
            printf("            [ITME] : '%s' '%s'\n",TYPE,VALUE);

            PACKSize++;
            PACK = realloc(PACK, sizeof(char **) * (PACKSize));
            PACK[PACKSize - 1] = _while[i];
        }
        if (_whileSize - 1 == i) {
            char ***countPack;
            int countPackSize;

            COUNT(PACK, PACKSize, &countPack, &countPackSize,MEMORY_GROUP);

            PACKSize = 0;
            free(PACK);
            PACK = malloc(sizeof(char **));
            if (strcmp(countPack[0][0], "ERR") == 0) {
                int thisLine = 1;
                int lastLine =0;

                int vindex=-1;
                printf("nnn %d\n",Index_);
                for (int i = 0; i < NL; i++) {



                    thisLine = i+1;
                    if (EveryLines[i] < Index_) {

                    } else {
                        break;
                    }
                    if (vindex == EveryLines[i]){}else{
                        lastLine = i+1;
                        vindex=EveryLines[i];
                    }

                }


                char ***Err = malloc(sizeof(char**));
                Err[0] = malloc(sizeof(char*)*5);
                Err[0][0] = "ERR";
                Err[0][1] = countPack[0][1];

                for (int i = 0; i < 5; i++) {
                    printf("return pack %s\n",countPack[0][i]);
                }
                Err[0][2] = countPack[0][2];
                Err[0][3] = malloc(12);
                if (countPack[0][3]==NULL){
                    sprintf( Err[0][3], "%d", thisLine);
                    printf("Touched\n");
                }else{
                    sprintf( Err[0][3], "%d", thisLine-atoi(countPack[0][4])+ atoi(countPack[0][3]));
                    printf("%s\n",Err[0][3]);
                }
                Err[0][4] = malloc(12);
                sprintf(Err[0][4], "%d",NL-1);
                *OUTPUT = Err;
                *OPSize = 1;

                return;
            }
            *OPSize = countPackSize;
            *OUTPUT = countPack;
            printf("        [END HEAD: RETURN ; Warring : End by \"return\" HEAD.]\n\n");
            return;
        }


    }
    printf("        [END HEAD: RETURN]\n\n");
}
void get(char*** _while,int _whileSize,int firstI,int* OPSize,char* *** OUTPUT,char *** fucIn,int fucInSize,int MEMORY_GROUP,int NL,int* EveryLines ){

}


#endif
