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
    int state[] = {
        0, // 是否在限制別類裡，如果是則此項表示限制別類的類型。例如：字串=1, 表單=2, 函數=3,
        0, //是否為特殊字符 '\' 的後項，表示 '\'後(包含)有多少字元進行運算
        0, //為 '\'符號的特殊項，表示這個 backslashOption 有 '(' (1) 以及 ')' (2)符號
        0, //為 '\'符號的特殊項, 表示這個特殊符號的功能是什麼 例 : 1 = 回傳換行值 (10) , 2 = 回傳自訂字元...
    };

    char*backslashOption =  malloc(0);

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


        switch (state[0])
        {
        case 1:
            if (state[1])
            {
                state[1]++;

                backslashOption = realloc(backslashOption,state[1]);
                backslashOption[state[1]-1] = c;


                if (state[1]>2)
                {
                    if (c == '(')
                    {
                        state[2] = 1;
                    }else  if (c == ')')
                    {
                        if (state[2]==1)
                        {
                            state[2] = 2;
                        }
                    }
                }


                if (state[1]==2)
                {
                    switch (c)
                    {
                    case 'n':
                        state[3] = 1;
                        break;
                    case 'u':
                        state[3] = 2;
                        break;
                    case '\'':
                        state[3] = 3;
                        break;
                    case '"':
                        state[3] = 4;
                        break;
                    }
                }

                char* Cs = malloc(0); //每個模式自己個用
                int CsSize = 0;//_msize()

                switch (state[3])
                {
                case 1:
                    CASESize++;
                    CASE = realloc(CASE,CASESize);
                    CASE[CASESize-1] = 10;

                    state[3] = 0;
                    state[2] = 0;
                    state[1] = 0;

                    break;
                case 2:
                    if (state[2] == 2) //end
                    {
                        CASESize++;
                        CASE = realloc(CASE,CASESize);
                        CASE[CASESize-1] = 10;
                        //int unStart = cIndex - state[1] + 1 /* '/' */ +  1 /* Opt符號 */  + 1 /* '(' */ + (1);
                        //int unEnd = cIndex-(1);

                        int isHex = 0;
                        for (int i = 1/* 不要 '(' */ ; i<CsSize;i=+2)
                        {
                            if (i == 1) if (Cs[i] == '0' &&  Cs[i+1] == 'x') isHex = 1;

                        }

                        state[3] = 0;
                        state[2] = 0;
                        state[1] = 0;
                    }else if(state[2] == 1) //還在紀錄
                    {
                        CsSize++;
                        Cs = realloc(Cs,CsSize);
                        Cs[CsSize-1] = c;
                    }
                    break;

                }



            }
            break;
        }


        if (state[1]){}else
        {
            CASESize++;
            CASE = realloc(CASE,CASESize);
            CASE[CASESize-1] = c;

            switch (CharType)
            {
            case 3:
                if (state[0] == 1)
                {
                    if (state[1] == 0)
                    {
                        CASESize++;
                        CASE = realloc(CASE,CASESize);
                        CASE[CASESize-1] = c;
                        printf("*[CASE END]* ");
                        state[0] = 0;
                    }
                }else if (state[0] == 0)
                {
                    state[0] = 1;
                }

                break;
            case 12:

                if ( state[1]) //防止上方的結構有加了
                {
                }else
                {
                    state[1]++;
                    backslashOption = realloc(backslashOption,state[1]);
                    backslashOption[state[1]-1] = c;
                }
                break;
            }

            switch (state[0])
            {
            case 1://字串

                printf("*[CASE ADDED]* ");


                CASESize++;
                CASE = realloc(CASE,CASESize);
                CASE[CASESize-1] = c;

                break;

            }
        }




        printf("'%c' '%d' '%d'\n",c,CharType,state[0]);
    }while (1);

}


#endif //FILE_TO_CASE_OBJECTS_H
