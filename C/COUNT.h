void COUNT(char*** PACK, int PACKSize, char**** rePACK, int* rePACKSize,int MEMORY_GROUP);

#ifndef COUNT_H
#define COUNT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "run.h"
#include "memory.h"
#include "CASE_type.h"
#include "mione.h"
#include "prerr.h"


void FunctionCall(char**FunctionAddress,char*** Pack,int PackSize,char * ***rePack,int * rePackSize,int MEMORY_GROUP ) {
    printf("                    [FUNCTION CALL]:'%d'\n",MEMORY_GROUP);
    char *FucV = NULL;
    char* useless;

    to(FunctionAddress,&FucV,&useless,MEMORY_GROUP);


    if (FucV == NULL) {
        prerr(0, "ERR", -1);
    }

    for (int i = 0; i < strlen(FucV); i++) {
        if (i) {
            if (i == strlen(FucV) - 1) {
                FucV[i - 1] = 0;
            }
            else {
                FucV[i - 1] = FucV[i];
            }
        }
    }



    for (int i = 0;i<PackSize;i++){
        if (i){
            if (i==PackSize-1){
                Pack[i-1] = NULL;
            }else{
                Pack[i-1] = Pack[i];
            }
        }
    }
    PackSize = PackSize-2;



    memory=realloc(memory,sizeof(char***)*(MEMORY_GROUP+1+1));
    memory[MEMORY_GROUP+1] = NULL;
    mSize = realloc(mSize,sizeof(int)*(MEMORY_GROUP+1+1));
    mSize[MEMORY_GROUP+1] = 0;

    int ChildNL = 0;
    int * ChildEveryLine = NULL;

    char **Fuc = NULL;
    int Lines = 0;
    toBeCompileWithCode(FucV, &Fuc,&Lines);
    char***MIO=NULL;
    int c_size = compile(Fuc,Lines,&MIO,MEMORY_GROUP+1,&ChildNL,&ChildEveryLine);

    char ***FucReturn;
    int FucReturnSize = 0;

    char*** CountedWithV;
    int CountedWithVSize;
    COUNT(Pack,PackSize,&CountedWithV,&CountedWithVSize,MEMORY_GROUP+1);
    run(&FucReturn,&FucReturnSize,c_size, CountedWithV, CountedWithVSize,MIO,MEMORY_GROUP+1,ChildNL,ChildEveryLine);


    *rePack = FucReturn;
    *rePackSize = FucReturnSize;
}

void toErrForCasesCount(char* reason,char * code,char***Pack ) {
    static char* erPack[3];
    erPack[0] = "ERR";
    erPack[1] = code;
    erPack[2] = reason;

    *Pack = erPack;
}

void CasesCount(char***CASES,int CASESSize,char* ***rePack,int *rePackSize,int MEMORY_GROUP ){
    //case()()
    //x()
    //y


    int bracketLVL = 0;
    int beforeBracket = 0;

    int bracketType = 1;//0:Call Function 1:Choose Table Child

    char*** InBracket = malloc(0);
    int InBracketSize = 0;

    int FucReIsVs[]={
            0, //開始
            1 //長度
    };

    printf("%d\n",MEMORY_GROUP);


    for (int index = 0;index<CASESSize;index++) {
        printf("                [CASE COUNT]:'%s' '%s'\n",CASES[index][0],CASES[index][1]);

        if (bracketLVL) {
            printf("added : %s %s\n",CASES[index][0],CASES[index][1]);
            InBracketSize++;
            InBracket = realloc(InBracket, sizeof(char**) * InBracketSize);
            InBracket[InBracketSize - 1] = CASES[index];
        }
        else {


        }


        if (strcmp(CASES[index][0], "SYMBOL") == 0){
            if (strcmp(CASES[index][1], "7")==0){ // "("
                bracketType = 1;
                if (bracketLVL == 0) {
                    beforeBracket = index; //要加一 -1+1

                }


                if (bracketLVL) {}else {
                    printf("added on 7: %s %s\n",CASES[index][0],CASES[index][1]);

                    InBracketSize++;
                    InBracket = realloc(InBracket, sizeof(char**) * InBracketSize);
                    InBracket[InBracketSize - 1] = CASES[index];
                }
                bracketLVL++;
            }


            if (strcmp(CASES[index][1], "8")==0){ // ")"
                bracketLVL--;

                if (bracketLVL) {

                }
                else{
                    if (beforeBracket){
                        if (bracketType == 1) { // Calling Function
                            if (strcmp(CASES[beforeBracket-1][0], "VALUE") == 0 || strcmp(CASES[beforeBracket-1][0], "VARIABLE") == 0) {
                                char* VVType;//might be 4,Function
                                char*useless;


                                to(CASES[beforeBracket-1],&useless,&VVType,MEMORY_GROUP);


                                if (strcmp(VVType ,"4")==0) {
                                    char*** ReturnPACK;
                                    int ReturnPACKSize;

                                    FunctionCall(CASES[beforeBracket-1], InBracket, InBracketSize,&ReturnPACK,&ReturnPACKSize,MEMORY_GROUP);

                                    //CASES[beforeBracket-1] = NULL;
                                    //CASESSize--;
                                    if (ReturnPACKSize){
                                        if (strcmp(ReturnPACK[0][0], "ERR")==0){

                                            *rePack =ReturnPACK;
                                            *rePackSize = 1;


                                            return;
                                        }
                                    }

                                    if (ReturnPACKSize){
                                        FucReIsVs[0] = beforeBracket-1;
                                        FucReIsVs[1] = ReturnPACKSize;
                                    }
                                    int shit;
                                    if (ReturnPACKSize>1+InBracketSize){

                                        CASES = realloc(CASES, sizeof(char **) * (CASESSize + ReturnPACKSize));
                                        int wasMax = CASESSize;
                                        CASESSize = CASESSize + ReturnPACKSize;

                                        for (int i = 0; i < wasMax-beforeBracket+1; i++) {
                                            CASES[wasMax+i] = CASES[beforeBracket-1+i];
                                        }

                                        for (int i =0 ;i<ReturnPACKSize;i++){
                                            CASES[beforeBracket-1+i] = ReturnPACK[i];
                                        }
                                    }else{

                                        for (int i = 0;i<ReturnPACKSize;i++){
                                            CASES[beforeBracket-1+i] = ReturnPACK[i];
                                            shit = beforeBracket-1+i;
                                        }

                                        for (int i =0;i < 3-ReturnPACKSize;i++){
                                            CASES[beforeBracket-1+1+i] = CASES[beforeBracket-1+1+i+InBracketSize];
                                        }
                                        CASESSize = CASESSize - 3 + ReturnPACKSize;


                                        CASES = realloc(CASES, sizeof(char **) * (CASESSize));



                                    }


                                    index = beforeBracket-1;
                                    InBracketSize = 0;
                                    InBracket = NULL;
                                    InBracket = malloc(0);


                                    *rePackSize =0;


                                    //a()+1
                                    //@@@+1
                                    //1@@+1
                                    //1+1



                                }
                                else {
                                    static char** err;
                                    toErrForCasesCount("It is not a Function?", "1", &err);
                                    *rePack =&err;
                                    *rePackSize = 1;
                                    return;
                                }

                            }
                        }
                    }else{
                        char ***thePack = malloc(0);//沒有括號的 inBracket
                        int thePackSize = 0;

                        for (int i =0;i<InBracketSize;i++){
                            if (i == 0 || i == InBracketSize - 1){}else {
                                thePackSize++;
                                thePack = realloc(thePack, sizeof(char **) * InBracketSize);
                                thePack[thePackSize - 1] = InBracket[i];
                            }
                        }

                        for (int i = 0; i < thePackSize; i++) {
                            printf("cc : %s %s\n", thePack[i][0], thePack[i][1]);
                        }


                        if (thePackSize){
                            char ***CountedPACK;
                            int CountedPACKSize;

                            for (int i = 0; i < thePackSize; i++) {
                                printf("thePack : %s %s\n", thePack[i][0], thePack[i][1]);
                            }

                            COUNT(thePack, thePackSize, &CountedPACK, &CountedPACKSize, MEMORY_GROUP);

                            for (int i = 0; i < thePackSize; i++) {
                                printf("thePack : %s %s\n", thePack[i][0], thePack[i][1]);
                            }

                            for (int i = 0; i < CountedPACKSize; i++) {
                                printf("COUNTEDPACK : %s %s\n", CountedPACK[i][0], CountedPACK[i][1]);
                            }
                            *rePack = CountedPACK;
                            *rePackSize = CountedPACKSize;

                        }else{

                            static char a[] = "VALUE";
                            static char b[] = "0";
                            static char*  ni[] = {a,b};
                            static char** nil[] = {ni};

                            *rePack = nil;
                            *rePackSize = 1;
                        }
                    }

                }


                bracketType = 0; //end bracket
            }

        }
    }



    if (*rePackSize){
        if (strcmp(*rePack[0][0],"ERR")==0){

        }else{

        }
    }else{
        if (CASESSize){
            *rePack = CASES;
            *rePackSize = CASESSize;
        }else{
            static char a[] = "VALUE";
            static char b[] = "0";
            static char*  ni[] = {a,b};
            static char** nil[] = {ni};

            *rePack = nil;
            *rePackSize = 1;
        }

    }
}

void COUNT (char***PACK,int PACKSize,char * ***rePACK,int * rePACKSize,int MEMORY_GROUP ){ //

    char ***CASES = malloc(0); // a()
    int CASESSize = 0;

    char ***Pack = malloc(0); // 1 + a()
    int PackSize = 0;

    int lvl = 0;

    for (int index = 0;index<PACKSize;index++) {
        printf("                [COUNT]:'%s' '%s'\n",PACK[index][0],PACK[index][1]);
        int addCASE = 0;
        int countCASE = 0;

        if (PACKSize-1 == index) {countCASE = 1,addCASE = 1;};

        if (strcmp(PACK[index][0], "SYMBOL") == 0)  if (strcmp(PACK[index][1], "7") == 0) lvl++;
       

        if (strcmp(PACK[index][0], "VALUE") == 0 || strcmp(PACK[index][0], "VARIABLE") == 0) addCASE = 1;
        if (strcmp(PACK[index][0], "SYMBOL") == 0) if (SYMBOL_CASE[atoi(PACK[index][1]) - 1].COUNT == 0) addCASE = 1;

        if (addCASE || lvl) {
            int shit =0;
            if (strcmp(PACK[index][0], "SYMBOL") == 0) {
                //if (SYMBOL_CASE[atoi(PACK[index][1]) - 1].COUNT == 1){}else

                shit = 1;
            }else shit = 1;

            if (shit){
                CASESSize++;
                CASES = realloc(CASES, sizeof(char **) * (CASESSize));
                CASES[CASESSize - 1] = PACK[index];
            }

        }


        if (strcmp(PACK[index][0], "SYMBOL") == 0) if (SYMBOL_CASE[atoi(PACK[index][1]) - 1].COUNT == 1) countCASE = 1;

        if (countCASE && ( lvl==0 || PACKSize-1 == index)) {


            char ***thatRerPack;
            int thatRerPackSize = 0;

            CasesCount(CASES, CASESSize, &thatRerPack,&thatRerPackSize,MEMORY_GROUP);
            if (thatRerPackSize){

                if (strcmp(thatRerPack[thatRerPackSize - 1][0], "ERR")==0){

                    for (int i = 0;i<5;i++){
                        printf("my boy : %s\n",thatRerPack[0][i]);
                    }

                    *rePACK = thatRerPack;
                    *rePACKSize = 1;


                    return;
                }else{

                    for (int ii =0;ii<thatRerPackSize;ii++){
                        printf("REPACK : %s %s\n",thatRerPack[ii][0],thatRerPack[ii][1]);
                        PackSize++;
                        Pack = realloc(Pack, sizeof(char **) * (PackSize));
                        Pack[PackSize-1] = malloc(sizeof(char*)*2);

                        to(thatRerPack[ii],&(Pack[PackSize-1][0]),&(Pack[PackSize-1][1]),MEMORY_GROUP);
                        printf("is : %s %s\n",Pack[PackSize-1][0],Pack[PackSize-1][1]);

                    }
                }


                CASES = NULL;
                CASES = malloc(0);
                CASESSize = 0;

            }else{
                //how?!!!
            }

            if (strcmp(PACK[index][0], "SYMBOL")==0){
                if (SYMBOL_CASE[atoi(PACK[index][1]) - 1].COUNT == 1) {
                    printf("ME ADD %s\n",PACK[index][1]);
                    PackSize++;
                    Pack = realloc(Pack, sizeof(char **) * (PackSize));
                    Pack[PackSize - 1] = PACK[index];
                }

            }

        }


        if (strcmp(PACK[index][0], "SYMBOL") == 0)  if (strcmp(PACK[index][1], "8") == 0) lvl--;
    }

    printf("abc : %d\n",PackSize);

    for (int i = 0;i<PackSize;i++) {
        printf("PACK : %s %s\n",Pack[i][0],Pack[i][1]);
    }

    printf("end\n");

    char *nowSymbol = "0"; //這在外面我看了好頭痛
    for (int i = 0;i<PackSize;i++){
        int MaxLevel = 3;

        //Pack[i][0]; // `$print()@` or `SYMBOL`
        //Pack[i][1]; // `4`:type or `1`:address


        if (strcmp(Pack[i][0],"SYMBOL")==0){
            for (int level = 0;level<MaxLevel;level++){
                int nowLevel = MaxLevel - level;

                if (nowLevel == 3){
                    if (strcmp(Pack[i][1],"2")==0){//我知道這很白目，但我喜歡這樣寫
                        nowSymbol = "2";
                        break;
                    }else if (strcmp(Pack[i][1],"3")==0){
                        nowSymbol = "3";
                        break;

                    }
                }
            }
        }else{
            //VV會通過
            if (strcmp(nowSymbol,"0")==0){}else{
                if (strcmp(nowSymbol,"2")==0){ //我記得這是 "-" 號
                    char** toSub = Pack[i-2]; // `1` - 1
                    char** subTo = Pack[i]; // 1 - `1`

                    if (strcmp(toSub[1],"5")==0 && strcmp(subTo[1],"5")==0){
                        int minuend = atoi(toSub[0]);
                        int subtrahend = atoi(subTo[0]);

                        int size = snprintf(NULL, 0, "%d", minuend-subtrahend) + 1;



                        char out[size];
                        sprintf(out,"%d",minuend-subtrahend);

                        Pack[i-2][1] = "5";
                        Pack[i-2][0] = out;

                        for (int ii = 0;ii<PackSize;ii++){
                            if (ii>PackSize-i){
                                Pack[ii-1] = Pack[ii];
                                Pack[ii+1] = NULL;
                            }

                        }
                        PackSize = PackSize-2;
                        Pack = realloc(Pack, sizeof(char **) * (PackSize));

                        i = i-2;
                        nowSymbol = "0";
                    }else{
                        static char *errPack[3];
                        errPack[0] = "ERR";
                        errPack[1] = "0";
                        errPack[2] = "It's not a number.";
                        static char **erPack[] = {errPack};
                        *rePACK = erPack;
                        *rePACKSize = 1;
                        return;
                    }
                }else if (strcmp(nowSymbol,"3")==0){ //我記得這是 "+" 號
                    char** toSub = Pack[i-2]; // `1` + 1
                    char** subTo = Pack[i]; // 1 + `1`

                    if (strcmp(toSub[1],"5")==0 && strcmp(subTo[1],"5")==0){
                        int minuend = atoi(toSub[0]);
                        int subtrahend = atoi(subTo[0]);

                        int size = snprintf(NULL, 0, "%d", minuend+subtrahend) + 1;



                        char out[size];
                        sprintf(out,"%d",minuend+subtrahend);

                        Pack[i-2][1] = "5";
                        Pack[i-2][0] = out;

                        for (int ii = 0;ii<PackSize;ii++){
                            if (ii>PackSize-i){
                                Pack[ii-1] = Pack[ii];
                                Pack[ii+1] = NULL;
                            }

                        }
                        PackSize = PackSize-2;
                        Pack = realloc(Pack, sizeof(char **) * (PackSize));

                        i = i-2;
                        nowSymbol = "0";
                    }else{
                        static char *errPack[3];
                        errPack[0] = "ERR";
                        errPack[1] = "0";
                        errPack[2] = "It is not a number.";
                        static char **erPack[] = {errPack};
                        *rePACK = erPack;
                        *rePACKSize = 1;
                        return;
                    }
                }
            }
        }
    }

    if (strcmp(nowSymbol,"0")==0){

    }else{
        static char *errPack[3];
        errPack[0] = "ERR";
        errPack[1] = "0";
        errPack[2] = "SYMBOL need a VV after it.";
        static char **erPack[] = {errPack};
        *rePACK = erPack;
        *rePACKSize = 1;
        return;
    }
    for (int i = 0;i<PackSize;i++){
        char *ma;

        cm_v(&ma, atoi(Pack[i][1]),Pack[i][0],MEMORY_GROUP-1 < 0 ? 0 : MEMORY_GROUP -1 );
        Pack[i][0] = "VALUE";
        Pack[i][1] = ma;
    }

    *rePACK = Pack;
    *rePACKSize = PackSize;
}

#endif