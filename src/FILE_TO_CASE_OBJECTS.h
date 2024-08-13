//
// Created by chenn on 24-8-3.
//


#include <time.h>
CaseObj* FCO(FILE*F);

#ifndef FILE_TO_CASE_OBJECTS_H
#define FILE_TO_CASE_OBJECTS_H

int CheckCharType(const char Char)
{
    if ((Char>='a'&& Char<='z') || (Char>='A'&& Char<='Z')) return 1;

    if ((Char>='0'&& Char<='9')) return 2;

    if ((Char=='"')) return 3;

    if ((Char=='\'')) return 4;

    if ((Char=='{')) return 5;

    if ((Char=='}')) return 6;

    if ((Char=='$')) return 7;

    if ((Char=='@')) return 8;

    //Symbols

    char CanConnectWithAnotherSymbol[] = {
        '.',
        '*',
        '/',
        '-',
        '+'
    };

    char CanNotConnectWithAnotherSymbol[] = {
        '(',
        ')',
        '[',
        ']'
    };

    for (int i = 0;i<sizeof(CanConnectWithAnotherSymbol);i++)
    {
        if (CanConnectWithAnotherSymbol[i]==Char) return 9;
    }
    for (int i = 0;i<sizeof(CanNotConnectWithAnotherSymbol);i++)
    {
        if (CanNotConnectWithAnotherSymbol[i]==Char) return 10;
    }

    //space
    if (Char == ' ') return  11;

    if (Char == '\\') return 12;

    return 1;
}

CaseObj* FCO(FILE*F)
{
    int inLockinType = 0;  // 是否在限制別類裡，如果是則此項表示限制別類的類型。例如：字串=1, 表單=2, 函數=3

    int superCharSize = 0; //是否為特殊字符 '\' 的後項，表示 '\'後(包含)有多少字元進行運算

    int hasBracket = 0;//為 '\'符號的特殊項，表示這個 backslashOption 有 '(' (1) 以及 ')' (2)符號

    int superCharMode = 0; //為 '\'符號的特殊項, 表示這個特殊符號的功能是什麼 例 : 1 = 回傳換行值 (10) , 2 = 回傳自訂字元...


    char*backslashOption =  malloc(0);

    char* superCharOpt = malloc(0); //每個模式自己個用
    int superCharOptSize = 0;

    char *CASE = malloc(0);
    int CASESize = 0;

    char c = 0;
    int cIndex = -1;



    do
    {
        c = (char)fgetc(F);
        cIndex ++;
        if (c==EOF) break;

        int CharType = CheckCharType(c);


        switch (inLockinType)
        {
        case 1:
            if (superCharSize)
            {
               superCharSize++;

                backslashOption = realloc(backslashOption,superCharSize);
                backslashOption[superCharSize-1] = c;
                printf("*[SUPER CHAR ADD]* ");



                if (superCharSize>2)
                {
                    if (c == '(')
                    {
                       hasBracket = 1;
                    }else  if (c == ')')
                    {
                        if (hasBracket==1)
                        {
                           hasBracket = 2;
                        }
                    }
                }


                if (superCharSize==2)
                {
                    switch (c)
                    {
                    case 'n':
                       superCharMode = 1;
                        break;
                    case 'u':
                       superCharMode = 2;
                        break;
                    case '\'':
                       superCharMode = 3;
                        break;
                    case '"':
                       superCharMode = 4;
                        break;
                    }
                }



                switch (superCharMode)
                {
                case 1:
                    CASESize++;
                    CASE = realloc(CASE,CASESize);
                    CASE[CASESize-1] = 10;

                   superCharMode = 0;
                   hasBracket = 0;
                   superCharSize = 0;

                    break;
                case 2:
                    if (hasBracket == 2) //end
                    {
                        CASESize++;
                        CASE = realloc(CASE,CASESize);
                        CASE[CASESize-1] = 10;
                        //int unStart = cIndex -superCharSize + 1 /* '/' */ +  1 /* Opt符號 */  + 1 /* '(' */ + (1);
                        //int unEnd = cIndex-(1);

                        int isHex = 0;

                        for (int i = 1/* 不要 '(' */ ; i<superCharOptSize;i=i+2)
                        {
                            if (i == 1) if (superCharOpt[i] == '0' &&  superCharOpt[i+1] == 'x') isHex = 1;
                            if (isHex) if (superCharOptSize%2==1) break; //err
                            printf("a : %c %c\n",superCharOpt[i],superCharOpt[i+1]);
                        }

                       superCharMode = 0;
                       hasBracket = 0;
                       superCharSize = 0;
                    }else if(hasBracket == 1) //還在紀錄
                    {
                        superCharOptSize++;
                        superCharOpt = realloc(superCharOpt,superCharOptSize);
                        superCharOpt[superCharOptSize-1] = c;

                    }
                    break;

                }



            }
            break;
        }


        if (superCharSize){}else
        {
            CASESize++;
            CASE = realloc(CASE,CASESize);
            CASE[CASESize-1] = c;

            switch (CharType)
            {
            case 3:
                if (inLockinType == 1)
                {
                    if (superCharSize == 0)
                    {
                        CASESize++;
                        CASE = realloc(CASE,CASESize);
                        CASE[CASESize-1] = c;
                        printf("*[CASE END]* ");
                       inLockinType = 0;
                    }
                }else if (inLockinType == 0)
                {
                   inLockinType = 1;
                }

                break;
            case 12:

                if (superCharSize) //防止上方的結構有加了
                {
                }else
                {
                    printf("*[SUPER CHAR START]* ");
                   superCharSize++;
                    backslashOption = realloc(backslashOption,superCharSize);
                    backslashOption[superCharSize-1] = c;
                }

                break;
            }
        }


        if (superCharSize){}else
        {
            switch (inLockinType)
            {
            case 1://字串

                printf("*[CASE ADDED]* ");


                CASESize++;
                CASE = realloc(CASE,CASESize);
                CASE[CASESize-1] = c;

                break;

            }
        }



        printf("'%c' '%d' '%d'\n",c,CharType,inLockinType);
    }while (1);

}


#endif //FILE_TO_CASE_OBJECTS_H
