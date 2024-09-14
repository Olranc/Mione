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
    "get",
};


MioneObj *CMO(CaseObj*CASES,int CASESIZE)
{
    MioneObj *MIONE;
    int MIONESIZE = 0;
    for (int i = 0; i <CASESIZE; i++)
    {
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
        }


        printf("'%d' '%s'\n",CASES[i].ObjType,CASES[i].ObjName);
    }
}

#endif //CASE_TO_MIONE_H
