//Case to Mione Object

//
// Created by calle on 24-7-27.
//

#include "hpsvv.h"
#include "value.h"
mioObj ctm(char*Case,int CaseType);

#ifndef CTM_H
#define CTM_H

mioObj ctm(char*Case,int CaseType)
{

    mioObj obj = {
        .CaseType=0
    };



    if (CaseType==1 && CaseType == 7 && CaseType == 8)
    {
        for (int i = 0; i < sizeof(Heads)/sizeof(Heads[0]); i++)
        {
            if (strcmp(Heads[i],Case)==0)
            {
                obj.CaseType=HEAD;
                obj.CaseSelf=i+1;
                return obj;

            }
        }

        for (int i = 0; i < sizeof(Prompts)/sizeof(Prompts[0]); i++)
        {
            if (strcmp(Prompts[i],Case)==0)
            {
                obj.CaseType=PROMPT;
                obj.CaseSelf=i+1;
                return obj;
            }
        }

        for (int i = 0; i < sizeof(Prompts)/sizeof(Prompts[0]); i++)
        {
            if (strcmp(Prompts[i],Case)==0)
            {
                obj.CaseType=SYMBOL;
                obj.CaseSelf=i+1;
                return obj;
            }
        }
    }else
    {
        switch (CaseType)
        {
            case 2:
                obj.CaseType=VALUE;
                obj.value_object=createValue(Case,CaseType);

                break;
        }
    }







    return obj;

}

#endif //CTM_H
