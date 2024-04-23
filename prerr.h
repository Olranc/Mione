
#include "verson.h"

int prerr(int line, char* msg, int errCode) {
    printf("The Error on : %d\n-It said : %s \n", line, msg);
    printf("	Mione       :   '%s'\n", mione_verson);
    printf("	ErrCode    :   '%d'\n", errCode);

    exit(0);
    return 1;
}