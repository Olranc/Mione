int prerr(int line, char* msg, int errCode);
#include "version.h"
#ifndef _PRERR_H_
#define _PRERR_H_

int prerr(int line, char* msg, int errCode) {
    printf("The Error on : %d\n-It said : %s \n", line, msg);
    printf("	Mione       :   '%s'\n", mione_version);
    printf("	ErrCode    :   '%d'\n", errCode);

    exit(0);
    return 1;
}
#endif