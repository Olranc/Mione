int prerr(int line, char* msg, int errCode);
#include "version.h"
#ifndef _PRERR_H_
#define _PRERR_H_

int prerr(int line, char* msg, int errCode) {
    printf("\033[41;33m The Error on : %d \033[0m  \n\033[45;37m# %s \033[0m \n", line, msg);
    printf("	Mione       :  \033[44;37m '%s'\033[0m\n", mione_version);
    printf("	ErrCode    :   \033[41;33m'%d'\033[0m\n", errCode);

    exit(0);
    return 1;
}
#endif