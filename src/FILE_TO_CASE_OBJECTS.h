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

    return 1;
}

CaseObj* FCO(FILE*F)
{
    int state[] = {
        0, // 是否在限制別類裡，如果是則此項表示限制別類的類型。例如：字串=1, 表單=2, 函數=3,
    };
    char c = 0;
    do
    {
        c = (char)fgetc(F);
        if (c==-1) break;

        int CharType = CheckCharType(c);

        printf("'%c' '%d'\n",c,CharType);
    }while (1);

}


#endif //FILE_TO_CASE_OBJECTS_H
