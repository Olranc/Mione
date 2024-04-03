#ifndef run_h
#define run_h

#include "CASE_type.h"

char**** MIO = NULL;
int * MIOsize;
int MioTarget = 0;

int cSize = 0; //給mio.h的臨時變數

int NumberOfLines;
int* EveryLines = NULL; //每行的最後一個
int nowTarget = 0; //構建到...
int soNowLine = 1; //實體運行到...

int run() {
    if (MIOsize){
        MIOsize = realloc(MIOsize,sizeof (int)*(MioTarget+1));
    }else{
        MIOsize = malloc(sizeof (int));
    }
    MIOsize[MioTarget] = cSize;

    for (int i = 0;i<MIOsize[MioTarget];i++){ //HERE
        char * TYPE = MIO[MioTarget][i][0];
        char * ADDRESS = MIO[MioTarget][i][1];

        if (strcmp(TYPE,"HEAD")){ }else{//節省參訪時間
            for (int i = 0;i<sizeof(HEAD_CASE)/sizeof(HEAD_CASE[0]);i++){
                if (strcmp(HEAD_CASE[i].NAME, ADDRESS )){}else{
                    printf("OMG paired with HEAD\n");
                }
            }
        }

        if (strcmp(TYPE,"VALUE")==0 || strcmp(TYPE,"VARIABLE")==0 ){//節省參訪時間
            //to do
        }

        printf("%s %s\n",TYPE,ADDRESS);
    }
};


#endif // !run_h
