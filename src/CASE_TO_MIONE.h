//
// Created by calle on 24-9-7.
//


#include <tgmath.h>
MioneObj *CMO(CaseObj*CASES,int CASESIZE,int* *ROWS,int * ROWSSIZE,int * SIZE);




#ifndef CASE_TO_MIONE_H
#define CASE_TO_MIONE_H


#include "main.h"


char* Prompts[] =
{
    "=",
    "then",
    "else"
};




MioneObj *CMO(CaseObj*CASES,int CASESIZE,
    int* *ROWS, int * ROWSSIZE,int * SIZE)
{
    MioneObj *MIONE = 0;
    int MIONESIZE = 0;

    int ChildCount = 0; //子項數量

    printf("ddd %d\n",CASESIZE);





    int LastPaired = 0;


    int Lock = -1; //被封鎖到...

    int RF = 0; //Range Function

    VariableObj* Vars = malloc(0);
    int VarsSize = 0;

    CaseObj* Area = malloc(0);
    int AreaSize = 0;


    for (int i = 0; i <CASESIZE; i++)
    {

       if (Lock != i)
       {
            int Paired =0; //Head Symbol Prompt Variable Value

           if (ROWS)
           {
               if (CASES[i].ObjType == 13 || CASESIZE-1 == i)
               {
                   (*ROWSSIZE)++;
                   (*ROWS) = realloc(*ROWS,( (*ROWSSIZE))*sizeof(int));
                   (*ROWS)[ (*ROWSSIZE)-1] = MIONESIZE+1;
               }
           }







        //HEAD
         if (ChildCount == 0) for (int Ci = 0; Ci < sizeof( HeadFucs)/sizeof(HeadFucObj); Ci++) if (strcmp(CASES[i].ObjName,HeadFucs[Ci].Name) == 0)
        {

            HeadObj Head = (HeadObj){
                .Name = CASES[i].ObjName,
            };

            (MIONESIZE)++;
             (MIONE) = (MioneObj*)realloc( (MIONE) ,(MIONESIZE)*sizeof(MioneObj));
             (MIONE)[(MIONESIZE)-1] = (MioneObj){
                .ObjType= 1,
                .Head = Head
            };

            Paired = 1;

        }
        //PROMPT
         if (ChildCount == 0) for (int Ci = 0; Ci < sizeof( Prompts)/sizeof( Prompts[0]); Ci++) if (strcmp(CASES[i].ObjName,Prompts[Ci]) == 0)
        {

            PromptObj Prompt = (PromptObj){
                .Name = CASES[i].ObjName,
            };

            (MIONESIZE)++;
            (MIONE) = (MioneObj*)realloc( (MIONE) ,(MIONESIZE)*sizeof(MioneObj));
            (MIONE)[(MIONESIZE)-1] = (MioneObj){
                .ObjType= 2,
                .Prompt = Prompt
            };
            Paired = 2;

        }



        //SYMBOL
         if (ChildCount == 0) for (int Ci = 0; Ci < sizeof( Symbols)/sizeof( Symbols[0]); Ci++) if (strcmp(CASES[i].ObjName,Symbols[Ci].Name) == 0)
        {



            SymbolObj Symbol = (SymbolObj){
                .Name = CASES[i].ObjName,
                .SymbolType = Symbols[Ci].SymbolType,
            };

            (MIONESIZE)++;
            (MIONE) = (MioneObj*)realloc( (MIONE) ,(MIONESIZE)*sizeof(MioneObj));
            (MIONE)[(MIONESIZE)-1] = (MioneObj){
                .ObjType= 3,
                .Symbol = Symbol
            };
            Paired = 3;

        }

        //Value : String
         if (ChildCount == 0) if (CASES[i].ObjType == 3)
        {

            Paired = 5;
            ValueObj Value = (ValueObj){.ValueType = 1, .String = CASES[i].ObjName};

            (MIONESIZE)++;
            (MIONE) = (MioneObj*)realloc( (MIONE) ,(MIONESIZE)*sizeof(MioneObj));
            (MIONE)[(MIONESIZE)-1] = (MioneObj){
                .ObjType= 5,
                .Val = Value
            };

        }


        //Value : Function



            //Value : Function or range END
           if (strcmp(CASES[i].ObjName,"end") == 0)
           {

               ChildCount--;
               if (ChildCount == 0) //僅包覆最高層的子向
               {
                   Paired = 5;

                   AreaObj eArea = (AreaObj){
                       .Area =Area,
                       .Size = AreaSize,
                       .Index = i+1-AreaSize
                   };

                   printf("zzz %d \n",AreaSize);


                   ValueObj Value = (ValueObj){
                       .ValueType = RF == 1 ? 5 : 4,
                       .Area = eArea,
                   };



                   (MIONESIZE)++ ;
                   (MIONE) = (MioneObj*)realloc(MIONE, (MIONESIZE)*sizeof(MioneObj));
                   (MIONE)[(MIONESIZE)-1] = (MioneObj){
                       .ObjType = 5,
                       .Val = Value,
                   };

                   Area = NULL;
                   Area = malloc(0);
                   AreaSize = 0;




               }else
               {
                   AreaSize++;
                   Area = realloc(Area,AreaSize*sizeof(CaseObj));
                   Area[AreaSize-1] = CASES[i];


               }
           }else
           {
               if (ChildCount)
               {
                   AreaSize++;
                   Area = realloc(Area,AreaSize*sizeof(CaseObj));
                   Area[AreaSize-1] = CASES[i];


               }

           }

           if (strcmp(CASES[i].ObjName,"function") == 0)
           {
               ChildCount++;
               if (ChildCount == 1)
               {
                   RF = 2;
                   Paired = 5;

               }
           }


           //Value : Range


           if (strcmp(CASES[i].ObjName,"range") == 0)
           {
               ChildCount++;
               if (ChildCount == 1)
               {
                   RF = 1;
                   Paired = 5;

               }
           }




        //Value : NPNumber
            if (ChildCount == 0) if(CASES[i].ObjType == 2)
           {
               Paired = 5;


               long int V = 0;
               V=V+atoi(CASES[i].ObjName);

               ValueObj Value = (ValueObj){
                   .ValueType = 2,
                   .NPNumber = V
               };

               (MIONESIZE)++;
               (MIONE) = (MioneObj*)realloc( (MIONE) ,(MIONESIZE)*sizeof(MioneObj));
               (MIONE)[(MIONESIZE)-1] = (MioneObj){
                   .ObjType = 5,
                   .Val = Value,
               };

           }

        //Variable



         if (ChildCount == 0) if (Paired == 0 && (CASES[i].ObjType != 13))
        {
            Paired = 4;

            int NewVar = 1;

            VariableObj Variable;

            for (int j = 0; j < VarsSize; j++)   if (Vars[j].Name == CASES[i].ObjName)
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


            (MIONESIZE)++;
            (MIONE) = (MioneObj*)realloc( (MIONE) ,(MIONESIZE)*sizeof(MioneObj));
            (MIONE)[(MIONESIZE)-1] = (MioneObj){
                .ObjType = 4,
                .Var = Variable,
            };
        };





        if (!ChildCount) //一班執行的子項內容
        {

        }




        LastPaired = Paired;
       }
    }



/*
    int Size = 0;
    MioneObj** A = malloc(0);
    int* ASize = malloc(0);

    Size++;
    A = realloc(A,Size*sizeof(MioneObj));
    A[Size-1] = MIONE;
    ASize = realloc(ASize,Size*sizeof(int));
    ASize[Size-1] = MIONESIZE;

    for (int Index = 0; Index < Size; Index++)
    {
         for (int j = 0; j < 10; j++) printf("\033[1;37;41m LEVEL %d \033[0m",Index);
         printf("\n");


         char  string[] = {' '};
        for (int i = 0; i < ASize[Index]; i++)
        {
            printf("\033[0m %x :",i);
            if (A[Index][i].ObjType == 5)
            {
                printf("%s\033[1;37;42m VALUE \033[0m",string);
                switch (A[Index][i].Area.ValueType)
                {
                case 1:

                    printf("\033[1;37;45m String \033[0m : \033[1;34;47m %s \033[0m\n",A[Index][i].Area.String);
                    break;
                case 2:
                    printf("\033[1;37;45m NPNumber \033[0m : \033[1;34;47m %d \033[0m\n",A[Index][i].Area.NPNumber);
                    break;
                case 3:
                    printf("\033[1;37;45m PNumber \033[0m : \033[1;34;47m %Lf \033[0m\n",A[Index][i].Area.PNumber);
                    break;
                case 4:
                    printf("\033[1;37;45m Function \033[0m : \033[1;34;47m %p \033[0m\n",A[Index][i].Area.Area.Area);

                    Size++;
                    A = realloc(A,Size*sizeof(MioneObj));
                    A[Size-1] = A[Index][i].Area.Area.Area;
                    ASize = realloc(ASize,Size*sizeof(int));
                    ASize[Size-1] = A[Index][i].Area.Area.Size;

                    break;
                case 5:
                    printf("\033[1;37;45m Range \033[0m : \033[1;34;47m %p \033[0m\n",A[Index][i].Area.Area.Area);

                    Size++;
                    A = realloc(A,Size*sizeof(MioneObj));
                    A[Size-1] = A[Index][i].Area.Area.Area;
                    ASize = realloc(ASize,Size*sizeof(int));
                    ASize[Size-1] = A[Index][i].Area.Area.Size;

                    break;
                case 6:
                    printf("\033[1;37;45m Table \033[0m : \033[1;34;47m %p \033[0m\n",A[Index][i].Area.Table.Table);
                    break;
                }
                printf( "");
            }else

               switch (A[Index][i].ObjType)
               {
                     case 1:
                         printf("%s\033[1;37;42m HEAD \033[0m : \033[1;31;47m %s \033[0m\n",string,A[Index][i].Text);
                         break;
                     case 2:
                         printf("%s\033[1;37;42m PROMPT \033[0m : \033[1;31;47m %s \033[0m\n",string,A[Index][i].Text);
                         break;
                     case 3:
                         printf("%s\033[1;37;42m SYMBOL \033[0m : \033[1;31;47m %s \033[0m\n",string,A[Index][i].Text);
                         break;
                     case 4:
                         printf("%s\033[1;37;42m VARIABLE \033[0m : \033[1;31;47m %s \033[0m\n",string,A[Index][i].Var.Name);
                      break;
               }
        }

    }

*/

    (*SIZE) = (MIONESIZE);

    return MIONE;




}      



#endif //CASE_TO_MIONE_H