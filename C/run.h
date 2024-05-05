#ifndef run_h
#define run_h
#include "CASE_type.h"
#include "M.h"

int NL = 0;

char*** MIO = NULL;
int  MIOsize;
int MioTarget = 0;

int cSize = 0; //給mio.h的臨時變數


int* EveryLines = NULL; //每行的最後一個
int nowTarget = 0; //構建到...
int soNowLine = 1; //實體運行到...

int run() {
    MIOsize = cSize;

    int LOCK =0;

    for (int index = 0;index<MIOsize ;index++) { //HERE
        //printf("%s %s \n", MIO [index][0],MIO [index][1]);
        if (LOCK <= index){
            char *TYPE = MIO [index][0];
            char *ADDRESS = MIO [index][1];



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
                                lastIn = EveryLines[eLines]-1;
                               // printf("HEAD IN %d\n",lastIn);
                                break;
                            }

                        }



                        int lvl = 0;
                        int haveFullVV = 0;

                        for (int ii = 0; ii < MIOsize ; ii++) { //預測
                            if (ii > index) {
                                int Locked = 0;

                                if (strcmp(MIO [ii][0], "PROMPT") == 0){
                                    haveFullVV = 0;
                                }

                               // printf("OMG %s %s\n",MIO [ii][0],MIO [ii][1]);
                                if (strcmp(MIO [ii][0], "SYMBOL") == 0){

                                    int I = atoi(MIO[ii][1])-1;
                                    if (SYMBOL_CASE[I].VV){
                                        haveFullVV = 0;
                                    }else{
                                        if (strcmp(MIO[ii+1][0],"VALUE")||strcmp(MIO[ii+1][0],"VARIABLE")){
                                            haveFullVV = 1;
                                        }
                                    }
                                    if (strcmp(MIO [ii][1], "7")==0){
                                        lvl++;
                                        //printf("++\n");
                                    }
                                    if (strcmp(MIO [ii][1], "8")==0){
                                        lvl--;
                                        //printf("--\n");
                                    }
                                }



                                if (strcmp(MIO [ii][0], "VALUE") == 0 || strcmp(MIO [ii][0], "VARIABLE") == 0){

                                    if (lvl){}else{

                                        //if (ii<MIOsize -1){

                                        //}

                                        if (haveFullVV){
                                            canWrite = 0;
                                            Locked = 1;
                                            LOCK = ii;
                                            //printf("%d\n",ii);
                                            //printf("yess???? %s\n",MIO [ii][0]);
                                        }else{
                                            haveFullVV ++;
                                        }
                                    }



                                }


                                




                                if (strcmp(MIO [ii][0], "HEAD") == 0) {
                                    canWrite = 0;
                                }



                                //printf("HERE:%s %s %d\n",MIO [ii][0],MIO [ii][1],canWrite);

                                if (canWrite){
                                    PackSize++;
                                    PACK = realloc(PACK, sizeof(char **) * PackSize);
                                    PACK[PackSize - 1] = MIO [ii];

                                }else{
                                    if (Locked){
                                        Locked = 0;
                                    }else{
                                        LOCK = ii; //!!!
                                    }


                                    break;
                                }

                            }
                        }

                        if (canWrite){ //有時候很好奇之前是怎麼做到的w
                            LOCK = MIOsize -0;// 若正常，就要讓他便不正常w
                        }
                        //printf("here: %d\n",LOCK);
                        //printf("OMG paired with HEAD\n");
                        HEAD_CASE[i].fuc(PACK,PackSize);

                    }
                }
            }

            if (strcmp(TYPE, "VALUE") == 0 || strcmp(TYPE, "VARIABLE") == 0) {//節省參訪時間
                char ***PACK = malloc(sizeof(char **));
                int PackSize = 0;


                int canWrite = 1;

                int lastIn = 0;

                for (int eLines = 0; eLines < NL; eLines++) {
                    if (index<=(EveryLines[eLines]-1)){
                        lastIn = EveryLines[eLines]-1;
                        //printf("V/V IN %d\n",lastIn);
                        break;
                    }

                }



                int lvl = 0;
                int haveFullVV = 0;

                for (int ii = 0; ii < MIOsize ; ii++) { //預測
                    if (ii >= index) {
                        int Locked = 0;

                        if (strcmp(MIO [ii][0], "PROMPT") == 0){
                          haveFullVV = 0;
                        }

                        //printf("OMG %s %s\n",MIO [ii][0],MIO [ii][1]);
                        if (strcmp(MIO [ii][0], "SYMBOL") == 0){

                            int I = atoi(MIO[ii][1])-1;
                            if (SYMBOL_CASE[I].VV){
                                haveFullVV = 0;
                            }else{
                                if (strcmp(MIO[ii+1][0],"VALUE")||strcmp(MIO[ii+1][0],"VARIABLE")){
                                    haveFullVV = 1;
                                }
                            }
                            if (strcmp(MIO [ii][1], "7")==0){
                                lvl++;
                                //printf("++\n");
                            }
                            if (strcmp(MIO [ii][1], "8")==0){
                                lvl--;
                                //printf("--\n");
                            }
                        }



                        if (strcmp(MIO [ii][0], "VALUE") == 0 || strcmp(MIO [ii][0], "VARIABLE") == 0){

                            if (lvl){}else{

                                //if (ii<MIOsize -1){

                                //}

                                if (haveFullVV){

                                    canWrite = 0;
                                    Locked = 1;
                                    LOCK = ii;

                                    //printf("yess???? %s\n",MIO [ii][0]);

                                }else{
                                    haveFullVV ++;
                                }
                            }



                        }







                        if (strcmp(MIO [ii][0], "HEAD") == 0) {
                            canWrite = 0;
                        }



                        //printf("HERE:%s %s %d\n",MIO [ii][0],MIO [ii][1],canWrite);

                        if (canWrite){
                            PackSize++;
                            PACK = realloc(PACK, sizeof(char **) * PackSize);
                            PACK[PackSize - 1] = MIO [ii];

                        }else{
                            if (Locked){
                                Locked = 0;
                            }else{
                                LOCK = ii; //!!!
                            }


                            break;
                        }

                    }
                }

                if (canWrite){ //有時候很好奇之前是怎麼做到的w
                    LOCK = MIOsize -0;// 若正常，就要讓他便不正常w
                }
                //printf("here: %d\n",LOCK);
                //printf("OMG paired with HEAD\n");
                V_V(PACK,PackSize);

            }

        }

       // printf("MAIN:%s %s\n",TYPE,ADDRESS);
    }
};


#endif // !run_h
