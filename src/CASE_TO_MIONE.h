//
// Created by calle on 24-9-7.
//

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
};


MioneObj *CMO(CaseObj*CASES,int CASESIZE)
{
    MioneObj *MIONE;
    int MIONESIZE = 0;

    int ChildCount = 0; //子項數量

    for (int i = 0; i <CASESIZE; i++)
    {
        int Paired =0;
        //HEAD
        for (int Ci = 0; Ci < sizeof( Heads)/sizeof( Heads[0]); Ci++) if (strcmp(CASES[i].ObjName,Heads[Ci]) == 0)
        {
            MIONESIZE++;
            MIONE = (MioneObj*)malloc(MIONESIZE*sizeof(MioneObj));
            MIONE[MIONESIZE-1] = (MioneObj){
                .ObjType= 1,
                .Text = CASES[i].ObjName,
                .Area = NULL
            };
            Paired = 1;
        }
        //PROMPT
        for (int Ci = 0; Ci < sizeof( Prompts)/sizeof( Prompts[0]); Ci++) if (strcmp(CASES[i].ObjName,Prompts[Ci]) == 0)
        {
            MIONESIZE++;
            MIONE = (MioneObj*)malloc(MIONESIZE*sizeof(MioneObj));
            MIONE[MIONESIZE-1] = (MioneObj){
                .ObjType= 2,
                .Text = CASES[i].ObjName,
                .Area = NULL
            };
            Paired = 2;
        }
        //SYMBOL
        for (int Ci = 0; Ci < sizeof( Symbols)/sizeof( Symbols[0]); Ci++) if (strcmp(CASES[i].ObjName,Symbols[Ci]) == 0)
        {
            MIONESIZE++;
            MIONE = (MioneObj*)malloc(MIONESIZE*sizeof(MioneObj));
            MIONE[MIONESIZE-1] = (MioneObj){
                .ObjType= 3,
                .Text = CASES[i].ObjName,
                .Area = NULL
            };
            Paired = 3;
        }
        //Value : Function
        if (Paired == 0) if (strcmp(CASES[i].ObjName,"function") == 0) ChildCount++;
        if (Paired == 0) if (strcmp(CASES[i].ObjName,"range") == 0) ChildCount++;
        if (Paired == 0) if (strcmp(CASES[i].ObjName,"multi") == 0) ChildCount++;
        if (Paired == 0) if (strcmp(CASES[i].ObjName,"end") == 0) ChildCount--;

        printf("'%d' '%s'\n",CASES[i].ObjType,CASES[i].ObjName);
    }
}

#endif //CASE_TO_MIONE_H
