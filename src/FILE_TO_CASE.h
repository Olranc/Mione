//
// Created by chenn on 24-8-3.
//


CaseObj* FCO(FILE* F,int *CASESIZE);

#ifndef FILE_TO_CASE_OBJECTS_H
#define FILE_TO_CASE_OBJECTS_H

int CheckCharType(const char Char)
{
    if (Char == EOF) return 0;

    if ((Char >= 'a' && Char <= 'z') || (Char >= 'A' && Char <= 'Z')) return 1;

    if ((Char >= '0' && Char <= '9')) return 2;

    if ((Char == '"')) return 3;

    if ((Char == '\'')) return 4;

    if ((Char == '{')) return 5;

    if ((Char == '}')) return 6;

    if ((Char == '$')) return 7;

    if ((Char == '@')) return 8;

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

    for (int i = 0; i < sizeof(CanConnectWithAnotherSymbol); i++)
    {
        if (CanConnectWithAnotherSymbol[i] == Char) return 9;
    }
    for (int i = 0; i < sizeof(CanNotConnectWithAnotherSymbol); i++)
    {
        if (CanNotConnectWithAnotherSymbol[i] == Char) return 10;
    }

    //space
    if (Char == ' ') return 11;

    if (Char == '\\') return 12;

    return 1;
}

CaseObj* FCO(FILE* F,int*CASESIZE)
{
    CaseObj a = {
        .ObjName = "Name",
        .ObjType = 0,
    };
    CaseObj *CaseObjects = NULL;
    int CaseObjectsSize = 0;

    int inLockinType = 0; // 是否在限制別類裡，如果是則此項表示限制別類的類型。例如：字串=1

    int superCharSize = 0; //是否為特殊字符 '\' 的後項，表示 '\'後(包含)有多少字元進行運算

    int hasBracket = 0; //為 '\'符號的特殊項，表示這個 backslashOption 有 '(' (1) 以及 ')' (2)符號

    int superCharMode = 0; //為 '\'符號的特殊項, 表示這個特殊符號的功能是什麼 例 : 1 = 回傳換行值 (10) , 2 = 回傳自訂字元...

    int ThislastSuperChar = 0; //為 '\'符號的特殊項,為1時代表這是Super Char的最後一項，辨別使用

    int LastCharType = 0; //上個字元的別類

    char* backslashOption = malloc(0);

    char* superCharOpt = malloc(0); //每個模式自己個用
    int superCharOptSize = 0;

    char* superCharOut = malloc(0); //返回值
    int superCharOutSize = 0;

    char* CASE = malloc(0);
    int CASESize = 0;

    char c = 0;
    int cIndex = -1;

    do
    {
        c = (char)fgetc(F);
        cIndex++;

        int CharType = CheckCharType(c);


        switch (inLockinType)
        {
        case 1:
            if (superCharSize)
            {
                superCharSize++;

                backslashOption = realloc(backslashOption, superCharSize);
                backslashOption[superCharSize - 1] = c;
                //printf("*[SUPER CHAR ADD]* ");


                if (superCharSize > 2)
                {
                    if (c == '(')
                    {
                        hasBracket = 1;
                    }
                    else if (c == ')')
                    {
                        if (hasBracket == 1)
                        {
                            hasBracket = 2;
                        }
                    }
                }


                if (superCharSize == 2)
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
                    CASE = realloc(CASE, CASESize);
                    CASE[CASESize - 1] = 10;

                    superCharOut = NULL;
                    superCharOut = malloc(0);

                    superCharOutSize = 0;

                    for (int i = 0; i < superCharOptSize; i++) superCharOpt[i] = 0;
                    superCharOpt = NULL;
                    superCharOpt = malloc(0);

                    superCharOptSize = 0;

                    superCharMode = 0;
                    hasBracket = 0;
                    superCharSize = 0;
                    ThislastSuperChar = 1;
                    break;
                case 2:
                    if (hasBracket == 2) //end
                    {
                        //int unStart = cIndex -superCharSize + 1 /* '/' */ +  1 /* Opt符號 */  + 1 /* '(' */ + (1);
                        //int unEnd = cIndex-(1);

                        superCharOpt = realloc(superCharOpt, superCharOptSize);
                        superCharOpt[superCharOptSize] = 0;

                        int isHex = 0;
                        for (int i = 1/* 不要 '(' */ ; i < superCharOptSize; i = i + 2)
                        {
                            if (isHex) if ((superCharOptSize - 1/* '(' */) % 2 == 1) break;
                            if (i == 1)
                            {
                                if (superCharOpt[i] == '1' && superCharOpt[i + 1] == '6') isHex = 1;
                            }
                            else
                            {
                                const char A[] = {
                                    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
                                };

                                int indexA = 0; //個位
                                int indexB = 0; //十位


                                for (int index = 0; index < 16; index++)
                                {
                                    if (A[index] == superCharOpt[i + 1])
                                    {
                                        indexA = index;
                                    };
                                    if (A[index] == superCharOpt[i])
                                    {
                                        indexB = index;
                                    };
                                }

                                superCharOutSize++;
                                superCharOut = realloc(superCharOut, superCharOutSize);
                                superCharOut[superCharOutSize - 1] = indexB * 16 + indexA;
                            };
                        }


                        //for (int i =0;i<superCharOutSize;i++) {printf("A:%d %d\n",superCharOut[i],superCharOutSize);}


                        //for (int i =0;i<CASESize;i++) {printf("B:%d\n",CASE[i]);}

                        CASESize = CASESize + superCharOutSize;
                        CASE = realloc(CASE, CASESize);


                        for (int i = 0; i < superCharOutSize; i++)
                        {
                            CASE[i + CASESize - superCharOutSize] = superCharOut[i];
                        }


                        for (int i = 0; i < superCharOutSize; i++) superCharOut[i] = 0;

                        superCharOut = NULL;
                        superCharOut = malloc(0);

                        superCharOutSize = 0;

                        for (int i = 0; i < superCharOptSize; i++) superCharOpt[i] = 0;
                        superCharOpt = NULL;
                        superCharOpt = malloc(0);

                        superCharOptSize = 0;


                        superCharMode = 0;
                        hasBracket = 0;
                        superCharSize = 0;
                        ThislastSuperChar = 1;
                    }
                    else if (hasBracket == 1) //還在紀錄
                    {
                        superCharOptSize++;
                        superCharOpt = realloc(superCharOpt, superCharOptSize);
                        superCharOpt[superCharOptSize - 1] = c;
                    }
                    break;
                case 3:
                    CASESize++;
                    CASE = realloc(CASE, CASESize);
                    CASE[CASESize - 1] = '\'';

                    superCharOut = NULL;
                    superCharOut = malloc(0);

                    superCharOutSize = 0;

                    for (int i = 0; i < superCharOptSize; i++) superCharOpt[i] = 0;
                    superCharOpt = NULL;
                    superCharOpt = malloc(0);

                    superCharOptSize = 0;

                    superCharMode = 0;
                    hasBracket = 0;
                    superCharSize = 0;
                    ThislastSuperChar = 1;
                    break;
                case 4:
                    CASESize++;
                    CASE = realloc(CASE, CASESize);
                    CASE[CASESize - 1] = '"';

                    superCharOut = NULL;
                    superCharOut = malloc(0);

                    superCharOutSize = 0;

                    for (int i = 0; i < superCharOptSize; i++) superCharOpt[i] = 0;
                    superCharOpt = NULL;
                    superCharOpt = malloc(0);

                    superCharOptSize = 0;

                    superCharMode = 0;
                    hasBracket = 0;
                    superCharSize = 0;
                    ThislastSuperChar = 1;
                    break;
                }
            }
            break;
        }


        if (inLockinType)
        {
        }
        else
        {
            if (LastCharType == CharType)
            {
            }
            else //一般結束 沒有被限制的情況下
            {
                if (CASESize)
                {
                    CASESize++;
                    CASE = realloc(CASE, CASESize);
                    CASE[CASESize - 1] = 0;


                    //printf("case '%s'\n", CASE);
                    CaseObjectsSize++;
                    CaseObjects = realloc(CaseObjects, CaseObjectsSize*sizeof(a));
                    CaseObjects[CaseObjectsSize - 1] = (CaseObj){
                        .ObjType = LastCharType,
                        .ObjName = CASE,
                    };

                    CASE = NULL;
                    CASE = malloc(0);
                    CASESize = 0;
                }
            }
        }


        if (superCharSize || ThislastSuperChar)
        {
        }
        else //一般
        {
            switch (CharType)
            {
            case 1:
                if (inLockinType)
                {
                }
                else
                {
                    CASESize++;
                    CASE = realloc(CASE, CASESize);
                    CASE[CASESize - 1] = c;
                }

                break;
            case 2:
                if (inLockinType)
                {
                    CASESize++;
                    CASE = realloc(CASE, CASESize);
                    CASE[CASESize - 1] = c;
                    if (LastCharType == 1)
                    {
                        CharType = 1;
                    }

                }
                break;
            case 3:
                if (inLockinType == 1)
                {
                    CASESize++;
                    CASE = realloc(CASE, CASESize);
                    CASE[CASESize - 1] = c;

                    CASESize++;
                    CASE = realloc(CASE, CASESize);
                    CASE[CASESize - 1] = 0;
                    //printf("my track~ '%s'\n", CASE);

                    CaseObjectsSize++;
                    CaseObjects = realloc(CaseObjects, CaseObjectsSize*sizeof(a));
                    CaseObjects[CaseObjectsSize - 1] = (CaseObj){
                        .ObjType = 2,
                        .ObjName = CASE,
                    };

                    /*
                    for (int i = 0;i<CASESize;i++)
                    {
                        printf("%d %d\n",i,CASE[i]);
                    }
                    */

                    //printf("*[CASE END]* \n");


                    inLockinType = 0;

                    CASE = NULL;
                    CASE = malloc(0);
                    CASESize = 0;
                }
                else if (inLockinType == 0)
                {
                    inLockinType = 1;
                }

                break;
            case 10:
                if (!inLockinType)
                {
                    if (LastCharType == 10)
                    {
                        CASESize++;
                        CASE = realloc(CASE, CASESize);
                        CASE[CASESize - 1] = 0;

                        //printf("bdfr '%s'\n", CASE);

                        CaseObjectsSize++;
                        CaseObjects = realloc(CaseObjects, CaseObjectsSize*sizeof(a));
                        CaseObjects[CaseObjectsSize - 1] = (CaseObj){
                            .ObjType = 3,
                            .ObjName = CASE,
                        };

                        CASE = NULL;
                        CASE = malloc(0);
                        CASESize = 0;

                        CASESize++;
                        CASE = realloc(CASE, CASESize);
                        CASE[CASESize - 1] = c;
                    }
                    else
                    {
                        CASESize++;
                        CASE = realloc(CASE, CASESize);
                        CASE[CASESize - 1] = c;
                    }
                }

                break;
            case 12:
                if (superCharSize) //防止上方的結構有加了
                {
                }
                else
                {
                    // printf("*[SUPER CHAR START]* ");
                    superCharSize++;
                    backslashOption = realloc(backslashOption, superCharSize);
                    backslashOption[superCharSize - 1] = c;
                }

                break;
            }
        }


        if (superCharSize || ThislastSuperChar)
        {
        }
        else //Lockin 【內】專屬
        {
            switch (inLockinType)
            {
            case 1: //字串

                //printf("*[CASE ADDED]* \"%d\"",c);

                CASESize++;
                CASE = realloc(CASE, CASESize);
                CASE[CASESize - 1] = c;

                break;
            }
        }


        //printf("'%c' '%d' '%d'\n",c,CharType,inLockinType);
        LastCharType = CharType;
        ThislastSuperChar = 0;

        if (c == EOF) break;
    }
    while (1);

    *CASESIZE = CaseObjectsSize;
    return CaseObjects;
}


#endif //FILE_TO_CASE_OBJECTS_H