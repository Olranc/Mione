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

                        int lastIn = 0;

                        for (int eLines = 0; eLines < NL; eLines++) {
                            if (index<=(EveryLines[eLines]-1)){
                                lastIn = EveryLines[eLines]-1; //這 -1 在表單裡的邏輯....
                                printf("%d\n",lastIn);
                                break;
                            }

                        }

                        for (int ii = 0; ii < MIOsize[MioTarget]; ii++) {
                            if (ii > index) { // set x = fuc "hello"
                                if (strcmp(MIO[MioTarget][ii][0], "VALUE") == 0 || strcmp(MIO[MioTarget][ii][0], "VARIABLE") == 0) {
                                    if (ii < MIOsize[MioTarget]-1) {
                                        //printf("))))))) %d oh hi i am %s %s\n",ii,MIO[MioTarget][ii][0],MIO[MioTarget][ii][1]);
                                        if (strcmp(MIO[MioTarget][ii + 1][0], "VALUE") == 0 || strcmp(MIO[MioTarget][ii + 1][0], "VARIABLE") == 0) {
                                            if (lastIn<=ii){
                                                canWrite = 0;
                                                //因為這裡是 預測 ，若直接 canWrite = 0 ，自己也不會寫進去
                                                PackSize++;
                                                PACK = realloc(PACK, sizeof(char **) * PackSize);
                                                PACK[PackSize - 1] = MIO[MioTarget][ii];
                                            }
                                            //printf(")))))))))))))) %d i am %s %s\n",ii+1,MIO[MioTarget][ii + 1][0],MIO[MioTarget][ii + 1][1]);
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
                                        //printf("yes?\n");
                                    }
                                }

                                printf("HERE:%s %s %d\n",MIO[MioTarget][ii][0],MIO[MioTarget][ii][1],canWrite);

                                if (canWrite){
                                    PackSize++;
                                    PACK = realloc(PACK, sizeof(char **) * PackSize);
                                    PACK[PackSize - 1] = MIO[MioTarget][ii];

                                }else{
                                    LOCK = ii+1; //!!!
                                    break;
                                }

                            }
                        }

                        if (canWrite){ //有時候很好奇之前是怎麼做到的w
                            LOCK = MIOsize[MioTarget]-0;// 若正常，就要讓他便不正常w
                        }
                        //printf("here: %d\n",LOCK);
                        //printf("OMG paired with HEAD\n");
                        HEAD_CASE[i].fuc(PACK,PackSize);

                    }
                }
            }

            if (strcmp(TYPE, "VALUE") == 0 || strcmp(TYPE, "VARIABLE") == 0) {//節省參訪時間
                //我懶得用了
                char ***PACK = malloc(sizeof(char**));
                int PackSize =  0;

                int canWrite = 1;

                int lastIn = 0;

                for (int eLines = 0; eLines < NL; eLines++) {
                    if (index<=(EveryLines[eLines]-1)){
                        lastIn = EveryLines[eLines]-1; //這 -1 在表單裡的邏輯....
                        break;
                    }
                }


                for (int ii = 0; ii < MIOsize[MioTarget]; ii++) {
                    if (ii >= index){
                        for (int eLines = 0; eLines < NL; eLines++) {
                            if (lastIn < ii) {
                                //不同行
                                canWrite = 0;

                                //printf("%d %s\n",EveryLines[eLines],MIO[MioTarget][ii][1]);
                            }
                        }




                        if (canWrite){ //原來是這裡
                            PackSize++;
                            PACK = realloc(PACK, sizeof(char **) * PackSize);
                            PACK[PackSize - 1] = MIO[MioTarget][ii];
                        }else{
                            printf("Different %d %d\n",ii,index);
                            LOCK = ii;
                            break;
                        }
                    }
                }

                if (canWrite){
                    LOCK = MIOsize[MioTarget];
                    printf("didnt read %d\n",LOCK); //代表最後一行
                }

                VV(PACK,PackSize);
                printf("end\n");
            }

            if (strcmp(TYPE, "SYMBOL") == 0 ){
                //printf("aaaaaaaaaaaaaaaaaaa\n"); 當時在測試 LOCK用的
            }
        }

       // printf("MAIN:%s %s\n",TYPE,ADDRESS);
    }
};


#endif // !run_h
