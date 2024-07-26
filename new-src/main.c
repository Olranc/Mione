//系統檔
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//次要檔

#include "Obj.h"
#include "ftm.h"
#include "prerr.h"
#include "ttm.h"

int OMode (int main)
{
    switch (main)
    {
    case 'o':
        return 1;
    case 'i':
        return 2;
    default:
        return 0;
    }
}

int main(int OptionsNumber,char** Options) {

    switch  (OptionsNumber)
    {
        case 1:
            if(new("index.mio")==NULL)
            {
                prerr("Cannot create new file.",1,0);
            }
            break;
        default:
            int Mode = 0;
            for (int i = 1;i < OptionsNumber;i++)
            {
                const char* Opt = Options[i];

                if (Opt[0] == '-')
                {
                    Mode = OMode(Opt[1]);
                }

                if (Mode)
                {
                    switch (Mode)
                    {
                        case 1:
                        //開啟檔案
                            break;
                        case 2:
                        //開啟檔案
                            break;
                        default:
                            break;
                    }
                }
            }
            break;
    }
    return 0;
}
