int NL;
int* EveryLines;
void run(char* ***OUTPUT,int * OPSize,int MIOsize,char ***callingV,int callingVSize,char*** MIO,int MEMORY_GROUP );

#ifndef run_h
#define run_h
#include "CASE_type.h"
#include "M.h"


int* EveryLines = NULL;

void run(char* ***OUTPUT,int * OPSize,int MIOsize,char ***callingV,int callingVSize,char *** MIO,int MEMORY_GROUP  ) {
    printf("RUN!\n");
    int LOCK =0;

    int lvl =0;
    int lvlStar = 0;
    printf("MIOsize : %d\n",MIOsize);

    for (int index = 0;index<MIOsize ;index++) { //HERE
        printf("MAIN: %d %d %s %s\n",MIOsize,index,MIO [index][0],MIO [index][1]);
        if (LOCK <= index){
            char *TYPE = MIO [index][0];
            char *ADDRESS = MIO [index][1];

            lvl =0;

            if (strcmp(TYPE, "HEAD")) {}
            else {//節省參訪時間
                for (int i = 0; i < sizeof(HEAD_CASE) / sizeof(HEAD_CASE[0]); i++) {
                    if (strcmp(HEAD_CASE[i].NAME, ADDRESS)) {}
                    else {

                        char ***PACK = malloc(sizeof(char **));
                        int PackSize = 0;


                        int canWrite = 1;


                        for (int eLines = 0; eLines < NL; eLines++) {
                            if (index<=(EveryLines[eLines]-1)){
                               // printf("HEAD IN %d\n",lastIn);
                                break;
                            }

                        }



                        int haveFullVV = 0;

                        for (int ii = 0; ii < MIOsize ; ii++) { //預測
                            if (ii > index) {
                                int Locked = 0;

                                if (strcmp(MIO [ii][0], "PROMPT") == 0){
                                    haveFullVV = 0;
                                }


                                if (strcmp(MIO [ii][0], "SYMBOL") == 0){
                                    if (strcmp(MIO [ii][1], "7")==0){
                                        lvl++;
                                        lvlStar = ii+1;
                                    }
                                    if (strcmp(MIO [ii][1], "8")==0){
                                        lvl--;
                                        if (lvl){}else{
                                            lvlStar = 0;
                                        }
                                    }
                                    if (lvl==0){
                                        if (MIOsize != ii+1){
                                            if (strcmp(MIO [ii+1][0],"SYMBOL") == 0){
                                                haveFullVV = 0;
                                            }else{
                                                int I = atoi(MIO [ii][1]) - 1;
                                                if (SYMBOL_CASE[I].VV){
                                                    haveFullVV = 0;
                                                }else{
                                                    haveFullVV = 1;
                                                }
                                            }
                                        }
                                    }else{
                                        haveFullVV = 0;
                                    }
                                }




                                if (strcmp(MIO [ii][0], "VALUE") == 0 || strcmp(MIO [ii][0], "VARIABLE") == 0){

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
                        for (int i = 0; i < PackSize; i++){
                            printf("    HAHA:%s %s\n",PACK[i][0],PACK[i][1]);

                        }
                        HEAD_CASE[i].fuc(PACK,PackSize,index,OPSize,OUTPUT,callingV,callingVSize,MEMORY_GROUP);
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
                            if (strcmp(MIO [ii][1], "7")==0){
                                lvl++;
                                lvlStar = ii+1;
                            }
                            if (strcmp(MIO [ii][1], "8")==0){
                                lvl--;
                                if (lvl){}else{
                                    lvlStar = 0;
                                }
                            }
                            if (lvl==0){
                                if (MIOsize != ii+1){
                                    if (strcmp(MIO [ii+1][0],"SYMBOL") == 0){
                                        haveFullVV = 0;
                                    }else{
                                        int I = atoi(MIO [ii][1]) - 1;
                                        if (SYMBOL_CASE[I].VV){
                                            haveFullVV = 0;
                                        }else{
                                            haveFullVV = 1;
                                        }
                                    }
                                }
                            }else{
                                haveFullVV = 0;
                            }
                        }




                        if (strcmp(MIO [ii][0], "VALUE") == 0 || strcmp(MIO [ii][0], "VARIABLE") == 0){

                            if (haveFullVV){

                                canWrite = 0;
                                Locked = 1;
                                LOCK = ii;

                                //printf("yess???? %s\n",MIO [ii][0]);

                            }else{
                                haveFullVV ++;
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
                V_V(PACK,PackSize,index,MEMORY_GROUP);

            }

        }

       // printf("MAIN:%s %s\n",TYPE,ADDRESS);
    }

    if (lvl && lvlStar-1){
        int lastIn = 0;
        for (int eLines = 0; eLines < NL; eLines++) {
            if (lvlStar-1<=(EveryLines[eLines]-1)){
                lastIn = eLines+1;
                printf("V/V IN %d\n",lastIn);
                break;
            }

        }
        prerr(lastIn,"''(' or '[' did not match with ')', ']'",1);
    }

    char *my;
    char *mytype;
    printf("OPSIZE : %d\n",*OPSize);
    if (*OPSize > 0) {
        printf("A AS\n");
    }
    else {
        printf("MODED\n");
        *OPSize++;
        *OUTPUT = malloc(sizeof(char**));
        (*OUTPUT)[0] = malloc(sizeof(char*)*2);
        (*OUTPUT)[0][0] = "VALUE";
        (*OUTPUT)[0][1] = "0";
    }
    printf("err? %s %s\n",(*OUTPUT)[0][0],(*OUTPUT)[0][1]);
    to((*OUTPUT)[0], &my,&mytype,MEMORY_GROUP-1 < 0 ? 0 : MEMORY_GROUP-1); // memory.h

    printf("THIS POWER OFF : ADDRESS : %s %s (Type:%s)\n", (*OUTPUT)[0][1],my,mytype);
};


#endif // !run_h
