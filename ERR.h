//
// Created by calle on 24-11-16.
//

int WorkOnMioIndex = 0;

int * MioRowsEnd;
int MioRowsEndSize = 0;

void ErrCall();

#ifndef ERR_H
#define ERR_H

void ErrCall(char*Reason,char*ErrCode){
    int Line = 0;
    for (int i = 0; i < MioRowsEndSize; i++)
    {
        printf("%d %d\n",MioRowsEnd[i],WorkOnMioIndex);

       if (MioRowsEnd[i] < WorkOnMioIndex)
       {}else{
           Line = i+1;
           break;
       }
    }

    printf("\033[1;37;45m" "MIONE FAILED :(" "\033[0m" "\n");
    printf("\033[1;30;41m" "FAILED REASON : %s" "\033[0m" "\n",Reason);
    printf("\033[1;30;41m" "FAILED CODE : %s" "\033[0m" "\n",ErrCode);
    printf("\033[1;30;41m" "FAILED LINE: %d" "\033[0m" "\n" ,Line);

    exit(1);
}

#endif //ERR_H
