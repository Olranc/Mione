//Text to Mione Object

//
// Created by calle on 24-7-26.
//

#include "ctm.h"
mioObj* tts(const char**main,const int mainSLen);

#ifndef TTM_H
#define TTM_H

int AType(const char A) //參見 Mione-AType
{
    if (A >= 'a' && A<= 'z') return 1;
    if (A >= 'A' && A<= 'Z') return 1;
    if (A == '_') return 1;
    if (A >= '0' && A<= '9') return 2;
    if (A=='"') return 3;
    if (A=='\'') return 4;
    if (A=='{') return 5;
    if (A=='}') return 6;
    if (A=='$') return 7;
    if (A=='@') return 8;
    if (A=='\\') return 9;
    if (A=='/') return 10;
    if (A=='(' || A == ')') return 11; // 不可重疊
    if (A=='-' || A=='=') return 12; //可重疊
    return 1;
}

mioObj* tts(const char**main,const int mainSLen)
{

    int WordsType[] = { //參見 mione-wordsType
        0,//上個字元的A類型
        0,// 是否存在於限制類別當中
        0,// 上個字元是否在限制類別當中
        0,//是否為特殊符號後項
        0,//CASE類型(參見CASETYPE)
        0,//限制類別的最後項
    };

    mioObj *Objs = malloc(0);
    int ObjsSize = 0;

    char *Butter = malloc(0);
    int ButterSize = 0;

    for (int LineIndex =0;LineIndex<mainSLen;LineIndex++)
    {
        for (int TextIndex =0;TextIndex<strlen(main[LineIndex]);TextIndex++)
        {
            char Word = main[LineIndex][TextIndex];
            int ThisType= AType(Word);

            int isLast = LineIndex == mainSLen-1 && TextIndex == strlen(main[LineIndex])-1;
            int beMio = 0; //強制切換，通常用在不可重疊字符上


            if (!WordsType[1])
            {
                switch (ThisType)
                {
                case 1:
                    WordsType[4] = 1;
                    break;
                case 2: //數字
                    break;
                case 3: // "
                    WordsType[1] = 1;

                    break;
                case 9: // \

                    //WordsType[1] = 1;
                    break;
                case 10: // /

                    WordsType[1] = 5;
                    WordsType[4] = 0;
                    break;
                case 11:

                    if (WordsType[0] == 11)
                    {
                        beMio=1;
                    }
                    break;
                }
            }


            if ((ThisType != WordsType[0] /*需要不同別類*/ && WordsType[2] == 0 /*上一個字元需要不被類別限制*/ && WordsType[0]/*需要前面有字元*/)||WordsType[5])
            {
                ButterSize++;
                Butter = realloc(Butter,ButterSize);
                Butter[ButterSize-1] = '\0';

                //ObjsSize++;
                //Objs = realloc(Objs,ObjsSize);
                //Objs[ObjsSize-1] = ctm(Butter,WordsType[4]);
                printf("1 : %s\n",Butter);

                free(Butter);
                Butter = malloc(0);
                ButterSize = 0;
            }
            printf("%c %d\n",Word,WordsType[1]);
            ButterSize++;
            Butter = realloc(Butter,ButterSize);
            Butter[ButterSize-1] = Word;

            WordsType[5] = 0;

            if (WordsType[1])
            {
                switch (WordsType[1])
                {
                case 1: //字串
                    if (WordsType[2] == 1 && ThisType == 3)
                    {
                        WordsType[1] = 0;
                        WordsType[5] = 1;
                    }
                    break;
                }
            }

            if (isLast || beMio)
            {
                ButterSize++;
                Butter = realloc(Butter,ButterSize);
                Butter[ButterSize-1] = '\0';

                //ObjsSize++;
                //Objs = realloc(Objs,ObjsSize);
                //Objs[ObjsSize-1] = ctm(Butter,WordsType[4]);
                printf("2 : %s\n",Butter);

                free(Butter);
                Butter = malloc(0);
                ButterSize = 0;
            }





            WordsType[2] = WordsType[1];
            WordsType[0] = ThisType;
        }
    }
}


#endif //TTM_H
