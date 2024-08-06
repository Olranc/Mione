//
// Created by chenn on 24-8-3.
//


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
        0 //為 '\'符號的特殊項，表示這個 backslashOption 有 '('符號 --todo
    };

    char*backslashOption =  malloc(0);

    char *CASE = malloc(0);
    int CASESize = 0;

    char c = 0;
    do
    {
        c = (char)fgetc(F);
        if (c==-1) break;

        int CharType = CheckCharType(c);


        switch (state[0])
        {
        case 1:
            if (state[1])
            {
                state[1]++;

                backslashOption = realloc(backslashOption,state[1]);
                backslashOption[state[1]-1] = c;

                if (c == ')' && state[1]>2) //todo
                {

                }

                if ((c == 'n' || c == '\'' || c == '\"') && state[1]==2)
                {

                }

            }
            break;
        }

        if (state[1]){}else
        {
            switch (CharType)
            {
            case 3:
                if (state[0] == 1)
                {
                    if (state[1] == 0)
                    {
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
        }




        printf("'%c' '%d'\n",c,CharType);
    }while (1);

}


#endif //FILE_TO_CASE_OBJECTS_H
