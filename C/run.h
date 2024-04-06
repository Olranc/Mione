#ifndef run_h
#define run_h

#include "CASE_type.h"
int NL = 0;


char**** MIO = NULL;
int * MIOsize;
int MioTarget = 0;

int cSize = 0; //給mio.h的臨時變數


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

    int LOCK =0;

    for (int index = 0;index<MIOsize[MioTarget];index++) { //HERE
        if (LOCK <= index){
            char *TYPE = MIO[MioTarget][index][0];
            char *ADDRESS = MIO[MioTarget][index][1];

            if (strcmp(TYPE, "HEAD")) {}
            else {//節省參訪時間
                for (int i = 0; i < sizeof(HEAD_CASE) / sizeof(HEAD_CASE[0]); i++) {
                    if (strcmp(HEAD_CASE[i].NAME, ADDRESS)) {}
                    else {

                        char ***PACK = malloc(sizeof(char **));
                        int PackSize = 0;


                        int canWrite = 1;

                        for (int ii = 0; ii < MIOsize[MioTarget]; ii++) {
                            if (ii > index) { // set x = fuc "hello"
                                if (strcmp(MIO[MioTarget][ii][0], "VALUE") == 0 || strcmp(MIO[MioTarget][ii][0], "VARIABLE") == 0) {
                                    if (ii < MIOsize[MioTarget] - 1) {
                                        if (strcmp(MIO[MioTarget][ii + 1][0], "VALUE") == 0 || strcmp(MIO[MioTarget][ii + 1][0], "VARIABLE") == 0) {

                                            for (int eLines = 0; eLines < NL; eLines++) {
                                                if (EveryLines[eLines] > ii + 1&& EveryLines[eLines] >= ii + 1) {
                                                }else{
                                                    //不同行
                                                    canWrite = 0;
                                                }
                                            }


                                        }
                                    }
                                }

                                if (strcmp(MIO[MioTarget][ii][0], "HEAD") == 0) {
                                    canWrite = 0;
                                }

                                if (strcmp(MIO[MioTarget][ii][0], "SYMBOL") == 0){
                                    if (strcmp(MIO[MioTarget][ii][1], "9")==0){
                                        canWrite = 0;

                                        PackSize++;
                                        PACK = realloc(PACK, sizeof(char **) * PackSize);
                                        PACK[PackSize - 1] = MIO[MioTarget][ii];
                                    }
                                }


                                if (canWrite){
                                    PackSize++;
                                    PACK = realloc(PACK, sizeof(char **) * PackSize);
                                    PACK[PackSize - 1] = MIO[MioTarget][ii];
                                }else{
                                    LOCK = ii+1;
                                    break;
                                }

                            }
                        }

                        if (canWrite){
                            LOCK = MIOsize[MioTarget]-1; // 若正常，就要讓他便不正常w
                        }
                        printf("here: %d\n",LOCK);
                        //printf("OMG paired with HEAD\n");
                        HEAD_CASE[i].fuc(PACK,PackSize);

                    }
                }
            }

            if (strcmp(TYPE, "VALUE") == 0 || strcmp(TYPE, "VARIABLE") == 0) {//節省參訪時間
                //我懶得用了
            }

            if (strcmp(TYPE, "SYMBOL") == 0 ){
                //printf("aaaaaaaaaaaaaaaaaaa\n"); 當時在測試 LOCK用的
            }
        }

       // printf("MAIN:%s %s\n",TYPE,ADDRESS);
    }
};


#endif // !run_h
