//
// Created by calle on 24-9-7.
//

MioneObj *CMO(CaseObj*CASES,int CASESIZE);

#ifndef CASE_TO_MIONE_H
#define CASE_TO_MIONE_H

MioneObj *CMO(CaseObj*CASES,int CASESIZE)
{
    for (int i = 0; i <CASESIZE; i++)
    {
        printf("'%d' '%s'\n",CASES[i].ObjType,CASES[i].ObjName);
    }
}

#endif //CASE_TO_MIONE_H
