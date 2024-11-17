#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WELL_DONE 0
#define NO_FILE 1
#define FILE_NOT_FOUND 2
#define MEMORY_LEAKED 3
#define MIONE_FAILED 4

#define MIONE_VERSION "Sunfish-0.1"


#ifdef _WIN32

#endif

#ifdef __APPLE__

#endif

#ifdef __linux__

#endif



#include "ERR.h"
#include "OBJECTS.h"
#include "FILE_TO_CASE.h"
#include "HeadFile/AllHeads.h"
#include "CASE_TO_MIONE.h"
#include "MIONE.h"

int main(const int OptionsSize,char **Options)
{
    FILE *f = NULL;

    if (OptionsSize>1)
    {
        int Mode = 0;
        for (int i = 0;i<OptionsSize;i++)
        {
            int isChoosingMode = Options[i][0]=='-';

            if (Mode)
            {
                switch (Mode)
                {
                case 1:
                    f = fopen(Options[i],"r");
                    if (f){}else
                    {
                        return FILE_NOT_FOUND;
                    }
                    break;
                }
                Mode = 0;
            }

            if (isChoosingMode)
            {
                if (strcmp(strlwr(Options[i]),"-f")==0)  Mode = 1;
            }


        }
    }else
    {
        
        f = fopen("D:\\Mione\\index.mio","r");
    }


    if (f != NULL)
    {
        //MAIN
        int CaseObjSize = 0;
        CaseObj * CASES = FCO(f,&CaseObjSize);

        MioRowsEnd = malloc(0);
        int MioObjSize = 0;
        MioneObj * MioObj = CMO(CASES,CaseObjSize,&MioRowsEnd,&MioRowsEndSize,&MioObjSize);

        mione(MioObj,MioObjSize,MioRowsEnd);
    }else
    {
        return NO_FILE;
    }

    return WELL_DONE;
}
