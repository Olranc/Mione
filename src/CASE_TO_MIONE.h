//
// Created by calle on 24-9-7.
//

#include <inttypes.h>
#include <tgmath.h>
MioneObj *CMO(CaseObj*CASES,int CASESIZE,int* *ROWS);

#ifndef CASE_TO_MIONE_H
#define CASE_TO_MIONE_H


char* Heads[] =
{
    "set",
    "get",
    "if",
    "input",
};

char* Prompts[] =
{
    "=",
    "then",
    "else"
};

char* Symbols[] =
{
    "+",
    "-",
    ".",
    "==",
    "--"
};




MioneObj *CMO(CaseObj*CASES,int CASESIZE,int* *ROWS)
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

    int Minus = 1; //負號處理

    int LastPaired = 0;

    int ThisSourceHasBeenPN = 0; //是否已經有PNumber的數字

    int RowCount = 0; //行數

    int Lock = -1; //被封鎖到...

    VariableObj* Vars = malloc(0);
    int VarsSize = 0;

    printf("SIZE : %d\n",CASESIZE);

    for (int i = 0; i <CASESIZE; i++)
    {

       if (Lock != i)
       {
            int Paired =0; //Head Symbol Prompt Variable Value

        if (CASES[i].ObjType == 13)
        {
            RowCount++;
            (*ROWS) = realloc(*ROWS,(RowCount)*sizeof(int));
            (*ROWS)[RowCount-1] = i;
        }

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


        if (ThisSourceHasBeenPN) if (Paired ==1 || Paired == 2) ThisSourceHasBeenPN = 0;

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

        //Value : String
        if (CASES[i].ObjType == 3)
        {
            Paired = 5;
            ValueObj Value = (ValueObj){.ValueType = 1, .String = CASES[i].ObjName};

            (*DEFSIZE)++;
            (*DEF) = (MioneObj*)realloc( (*DEF) ,(*DEFSIZE)*sizeof(MioneObj));
            (*DEF)[(*DEFSIZE)-1] = (MioneObj){
                .ObjType= 5,
                .Area = Value
            };
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
                Paired = 5;

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
                Paired = 5;

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

            }
        }

        //Value : PNumber
        if (CASES[i].ObjType == 9) if (strcmp(CASES[i].ObjName,".") == 0)
        {
            if (CASESIZE-1>i)
            {
                if (!ThisSourceHasBeenPN)
                {
                    if (CASES[i+1].ObjType == 2)
                    {

                        (*DEFSIZE)--;
                        (*DEF)[(*DEFSIZE)] = (MioneObj){};

                        Lock = i+1;

                        ThisSourceHasBeenPN = 1;
                        long double V = 0;
                        V=V+atoi(CASES[i+1].ObjName)*pow(10.,(int)strlen(CASES[i+1].ObjName)*(-1));

                        if (i-1>=0)
                        {
                            if (CASES[i-1].ObjType == 2)
                            {

                                V=V+atoi(CASES[i-1].ObjName);
                            }
                        }

                        printf("%Lf\n",V);

                        Paired = 5;

                        ValueObj Value = (ValueObj){
                            .ValueType = 3,
                            .PNumber = V * (Minus),
                        };
                        Minus = 1;

                        (*DEFSIZE)++;
                        (*DEF) = (MioneObj*)realloc( (*DEF) ,(*DEFSIZE)*sizeof(MioneObj));
                        (*DEF)[(*DEFSIZE)-1] = (MioneObj){
                            .ObjType = 5,
                            .Area = Value,
                        };
                    }else if(i-1>=0 && CASES[i-1].ObjType == 2)
                    {
                        (*DEFSIZE)--;
                        (*DEF)[(*DEFSIZE)] = (MioneObj){};

                        ThisSourceHasBeenPN = 1;
                        long double V = 0;
                        V=V+atoi(CASES[i-1].ObjName);
                        ValueObj Value = (ValueObj){
                            .ValueType = 3,
                            .PNumber = V * (Minus),
                        };
                        Minus = 1;
                        (*DEFSIZE)++;
                        (*DEF) = (MioneObj*)realloc( (*DEF) ,(*DEFSIZE)*sizeof(MioneObj));
                        (*DEF)[(*DEFSIZE)-1] = (MioneObj){
                            .ObjType = 5,
                            .Area = Value,
                        };
                    }
                }else
                {
                    exit(0xffff+0x01);
                }

            }
        };




        //Value : NPNumber
        if (!Paired) // 防止PNumber搞怪
        {

            if ((CASESIZE-1>i &&( CASES[i+1].ObjType == 9 && (strcmp(CASES[i+1].ObjName,".") == 0))) ||
                (i-1>=0&&( CASES[i-1].ObjType == 9 && (strcmp(CASES[i-1].ObjName,".") == 0)))) //"."前的數字無法被Paired到，因此這樣做。
            { Paired = -1; }else if(CASES[i].ObjType == 2)
            {
                Paired = 5;


                long int V = 0;
                V=V+atoi(CASES[i].ObjName);

                ValueObj Value = (ValueObj){
                    .ValueType = 2,
                    .NPNumber = V * (Minus),
                };
                Minus = 1;

                (*DEFSIZE)++;
                (*DEF) = (MioneObj*)realloc( (*DEF) ,(*DEFSIZE)*sizeof(MioneObj));
                (*DEF)[(*DEFSIZE)-1] = (MioneObj){
                    .ObjType = 5,
                    .Area = Value,
                };

            }
        }

        //Variable

        if (Paired == 0 && (CASES[i].ObjType != 13))
        {
            Paired = 5;

            int NewVar = 1;

            VariableObj Variable;

            for (int j = 0; j < VarsSize; j++)   if (Vars[i].Name == CASES[i].ObjName)
            {

                NewVar = 0;
                Variable = Vars[i];
                break;
            }



            if (NewVar)
            {
                Variable = (VariableObj){
                    .Name = CASES[i].ObjName,
                };

                VarsSize++;
                Vars = realloc(Vars,VarsSize*sizeof(VariableObj));
                Vars[VarsSize-1] = Variable;
            }


            (*DEFSIZE)++;
            (*DEF) = (MioneObj*)realloc( (*DEF) ,(*DEFSIZE)*sizeof(MioneObj));
            (*DEF)[(*DEFSIZE)-1] = (MioneObj){
                .ObjType = 4,
                .Var = Variable,
            };
        };

        //**ELSE**

        //負數處理
        if (Paired == 3)
        {
            if (CASES[i].ObjType == 10) if (strcmp(CASES[i].ObjName,"-") == 0)
            {

                if (CASESIZE-1>i)
                {
                    if (CASES[i+1].ObjType == 2) Minus = -1;
                    if (CASES[i+1].ObjType == 9) if (strcmp(CASES[i+1].ObjName,".")==0)Minus = -1;
                }
            };
        }




        if (!ChildCount) //一班執行的子項內容
        {

        }


        printf("'%d' a'%s'\n",CASES[i].ObjType,CASES[i].ObjName);

        LastPaired = Paired;
       }
    }
    for (int i = 0; i < MIONESIZE; i++)
    {
        printf("\033[0m %d :",i);
        if (MIONE[i].ObjType == 5)
        {
            printf("\033[1;37;42m VALUE \033[0m");
            switch (MIONE[i].Area.ValueType)
            {
            case 1:

                printf("\033[1;37;45m String \033[0m : \033[1;34;47m %s \033[0m\n",MIONE[i].Area.String);
                break;
            case 2:
                printf("\033[1;37;45m NPNumber \033[0m : \033[1;34;47m %d \033[0m\n",MIONE[i].Area.NPNumber);
                break;
            case 3:
                printf("\033[1;37;45m PNumber \033[0m : \033[1;34;47m %Lf \033[0m\n",MIONE[i].Area.PNumber);
                break;
            case 4:
                printf("\033[1;37;45m Function \033[0m : \033[1;34;47m %p \033[0m\n",MIONE[i].Area.Area);
                break;
            case 5:
                printf("\033[1;37;45m Range \033[0m : \033[1;34;47m %p \033[0m\n",MIONE[i].Area.Area);
                break;
            case 6:
                printf("\033[1;37;45m Table \033[0m : \033[1;34;47m %p \033[0m\n",MIONE[i].Area.Table);
                break;
            }
            printf( "");
        }else
        {
            switch (MIONE[i].ObjType)
            {
            case 1:
                printf("\033[1;37;42m HEAD \033[0m : \033[1;31;47m %s \033[0m\n",MIONE[i].Text);
                break;
            case 2:
                printf("\033[1;37;42m PROMPT \033[0m : \033[1;31;47m %s \033[0m\n",MIONE[i].Text);
                break;
            case 3:
                printf("\033[1;37;42m SYMBOL \033[0m : \033[1;31;47m %s \033[0m\n",MIONE[i].Text);
                break;
            case 4:
                printf("\033[1;37;42m VARIABLE \033[0m : \033[1;31;47m %s \033[0m\n",MIONE[i].Var.Name);
                break;
            }
        }
    }
}

#endif //CASE_TO_MIONE_H