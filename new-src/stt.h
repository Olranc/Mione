//String to Table

//
// Created by calle on 24-7-27.
//

valObj *stt(const char *str);

#ifndef STT_H
#define STT_H

valObj *stt(const char *str)
{
    valObj *obj = malloc(0);


    int WordsType[] = { //參見 mione-wordsType
        0,//上個字元的A類型
        0,// 是否存在於限制類別當中
        0,// 上個字元是否在限制類別當中
        0,//是否為特殊符號後項
        0,//CASE類型(參見CASETYPE)
    };

    char **Cases = malloc(0);
    int CasesSize = 0;

    char *Butter = malloc(0);
    int ButterSize = 0;



    for (int i = 0; i < strlen(str); i++)
    {
        char Word = str[i];
        int ThisType= AType(Word);

        int isLast = i ==  strlen(str)-1;


        if (str[i]=='\n')
        {
            if (WordsType[0]==1 || WordsType[0] == 2)
            {
                WordsType[0] = 0;
            }
        }

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
        }

        if (ThisType != WordsType[0]/*需要不同別類*/ && WordsType[1] == 0/*需要不被類別限制*/ && WordsType[0]/*需要前面有字元*/)
        {
            ButterSize++;
            Butter = realloc(Butter,ButterSize);
            Butter[ButterSize-1] = '\0';

            CasesSize++;
            Cases = realloc(Cases,CasesSize);
            Cases[CasesSize-1] = Butter;

            free(Butter);
            Butter = malloc(0);
            ButterSize = 0;
        }

        ButterSize++;
        Butter = realloc(Butter,ButterSize);
        Butter[ButterSize-1] = Word;

        if (isLast)
        {
            ButterSize++;
            Butter = realloc(Butter,ButterSize);
            Butter[ButterSize-1] = '\0';

            CasesSize++;
            Cases = realloc(Cases,CasesSize);
            Cases[CasesSize-1] = Butter;

            free(Butter);
            Butter = malloc(0);
            ButterSize = 0;
        }




        WordsType[0] = ThisType;
    }


}

#endif //STT_H
