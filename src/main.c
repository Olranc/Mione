#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WELL_DONE 0
#define NO_FILE 1
#define FILE_NOT_FOUND 2
#define MEMORY_LEAKED 3

#include "OBJECTS.h"
#include "FILE_TO_CASE_OBJECTS.h"

int main(const int OptionsSize,char **Options)
{
    FILE *f = NULL;
    int Mode = 0;
    if (OptionsSize>1)
    {
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
        
        f = fopen("D:\\Chen99\\Mione\\index.mio","r");
    }


    if (f != NULL)
    {
        FCO(f);
    }else
    {
        return NO_FILE;
    }

    return WELL_DONE;
}
