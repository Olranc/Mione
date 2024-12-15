


#ifdef _WIN32

#endif

#ifdef __APPLE__

#endif

#ifdef __linux__

#endif

#include "main.h"


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
                        ErrCall("No file found","M001","");
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


        mione(MioObj,MioObjSize);
    }else
    {
        //todo
    }

    return 0;
}
