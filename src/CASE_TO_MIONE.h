//
// Created by calle on 24-9-7.
//

#include <inttypes.h>
#include <tgmath.h>
MioneObj *CMO(CaseObj*CASES,int CASESIZE);

#ifndef CASE_TO_MIONE_H
#define CASE_TO_MIONE_H


char* Heads[] =
{
    "set",
    "get",
};

char* Prompts[] =
{
    "=",
    "them",
};

char* Symbols[] =
{
    "+",
    "-",
    "."
};


MioneObj *CMO(CaseObj*CASES,int CASESIZE)
{
    MioneObj *MIONE = 0;
    int MIONESIZE = 0;

    int ChildCount = 0; //子項數量
    int ChildType = 0; //子項型態 1:Function 2:Range

    //子項
    MioneObj *Child = NULL;
    int ChildSIZE = 0; //子項大小

    MioneObj* *DEF = &MIONE;
    int * DEFSIZE = &MIONESIZE;

    for (int i = 0; i <CASESIZE; i++)
    {
        int Paired =0; //Head Symbol Prompt Variable Value
        //HEAD
        for (int Ci = 0; Ci < sizeof( Heads)/sizeof( Heads[0]); Ci++) if (strcmp(CASES[i].ObjName,Heads[Ci]) == 0)
        {
            (*DEFSIZE)++;
             (*DEF) = (MioneObj*)realloc( (*DEF) ,(*DEFSIZE)*sizeof(MioneObj));
             (*DEF)[(*DEFSIZE)-1] = (MioneObj){
                .ObjType= 1,
                .Text = CASES[i].ObjName,
                .Area = NULL
            };
            Paired = 1;
        }
        //PROMPT
        for (int Ci = 0; Ci < sizeof( Prompts)/sizeof( Prompts[0]); Ci++) if (strcmp(CASES[i].ObjName,Prompts[Ci]) == 0)
        {
            (*DEFSIZE)++;
            (*DEF) = (MioneObj*)realloc( (*DEF) ,(*DEFSIZE)*sizeof(MioneObj));
            (*DEF)[(*DEFSIZE)-1] = (MioneObj){
                .ObjType= 2,
                .Text = CASES[i].ObjName,
                .Area = NULL
            };
            Paired = 2;
        }
        //SYMBOL
        for (int Ci = 0; Ci < sizeof( Symbols)/sizeof( Symbols[0]); Ci++) if (strcmp(CASES[i].ObjName,Symbols[Ci]) == 0)
        {
            (*DEFSIZE)++;
            (*DEF) = (MioneObj*)realloc( (*DEF) ,(*DEFSIZE)*sizeof(MioneObj));
            (*DEF)[(*DEFSIZE)-1] = (MioneObj){
                .ObjType= 3,
                .Text = CASES[i].ObjName,
                .Area = NULL
            };
            Paired = 3;
        }



        //Value : Function

        if (ChildCount == 0) if (strcmp(CASES[i].ObjName,"function") == 0)
        {
            ChildCount++;
            if (ChildCount == 1)
            {
                ChildType=1;
                Paired = 4;

                DEF = &Child;
                DEFSIZE = &ChildSIZE;
            }
        }


        //Value : Range

        
        if (ChildCount == 0) if (strcmp(CASES[i].ObjName,"range") == 0)
        {
            ChildCount++;
            if (ChildCount == 1)
            {
                ChildType=2;
                Paired = 4;

                DEF = &Child;
                DEFSIZE = &ChildSIZE;
            }
        }

        // Value : Function or range END

        if (ChildCount != 0) if (strcmp(CASES[i].ObjName,"end") == 0)
        {
            ChildCount--;
            if (ChildCount == 0) //僅包覆最高層的子向
            {
                ChildType = 0;
                Paired = 4;

                DEF = &MIONE;
                DEFSIZE = &MIONESIZE;

                int a = ChildSIZE;


                ValueObj Value = (ValueObj){
                    .ValueType = Paired == 1 ? 4 : 5,
                    .Area = Child,

                    .String = NULL,
                    .NPNumber = 0,
                    .PNumber = 0,
                    .Table = NULL,
                };

                printf("%d\n",ChildSIZE);

                (*DEFSIZE)++ ;
                (*DEF) = (MioneObj*)realloc(*DEF, (*DEFSIZE)*sizeof(MioneObj));
                (*DEF)[(*DEFSIZE)-1] = (MioneObj){
                    .ObjType = 5,
                    .Text = NULL,
                    .Area = Value,
                };
                Child = NULL;
                ChildSIZE = 0;

                for (int i = 0; i < (a); i++)
                {
                    printf("aaa %s\n", Value.Area[i].Text);
                }
            }
        }

        //Value : NPNumber

        if (CASES[i].ObjType == 2)
        {
            Paired = 4;

            ValueObj Value = (ValueObj){
                .ValueType = 2,
                .NPNumber = atoi(CASES[i].ObjName)
            };

            (*DEFSIZE)++;
            (*DEF) = (MioneObj*)realloc( (*DEF) ,(*DEFSIZE)*sizeof(MioneObj));
            (*DEF)[(*DEFSIZE)-1] = (MioneObj){
                .ObjType= 5,
                .Text = NULL,
                .Area = Value
            };
        }


        //Value : PNumber
        if (CASES[i].ObjType == 2)  // 1.1
        {
            if (*DEFSIZE >= 3)
            {

                if ((*DEF)[(*DEFSIZE)-2].ObjType == 3)  if (strcmp((*DEF)[(*DEFSIZE)-2].Text,".")==0) // .
                {
                    if ((*DEF)[(*DEFSIZE)-3].ObjType == 5) if ((*DEF)[(*DEFSIZE)-3].Area.ValueType == 2)// 1.
                    {
                        long double V = 0;
                        V= V+ (*DEF)[(*DEFSIZE)-3].Area.NPNumber;

                        V= V+ (*DEF)[(*DEFSIZE)-1].Area.NPNumber*(pow(10.0,(int)(-1*strlen(CASES[i].ObjName))));

                        for (int i = 0;i<3;i++)
                        {
                            (*DEF)[(*DEFSIZE)-1] = (MioneObj){};
                            (*DEFSIZE)--;
                        }
                        printf("%Lf\n",V);

                    }
                }
            }

        }


        //Variable

        if (Paired == 0) Paired = 8;

        //



        if (!ChildCount) //一班執行的子項內容
        {

        }


        printf("'%d' '%s'\n",CASES[i].ObjType,CASES[i].ObjName);
    }
}

#endif //CASE_TO_MIONE_H