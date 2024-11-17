//
// Created by calle on 24-11-16.
//

int WorkOnMioIndex = 0;

int * MioRowsEnd;
int MioRowsEndSize = 0;

void ErrCall(char*Reason,char*ErrCode,char*Tip);

#ifndef ERR_H
#define ERR_H

void ErrCall(char*Reason,char*ErrCode,char*Tip){
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

    printf("\033[1;37;45m" " # MIONE FAILED :( \033[1;35;43m %s " "\033[0m" "\n",ErrCode);
    printf("    \033[1;37;41m" " $ REASON  " "\033[1;37;46m" " %s " "\033[0m" "\n",Reason);
    printf("    \033[1;37;41m" " $ LINE "  "\033[1;37;46m" " %d " "\033[0m" "\n" ,Line);
    printf("    \033[1;37;42m" " @ TIP "  "\033[1;36;40m" " %s " "\033[0m" "\n\n" ,Tip);

    printf("\033[1;37;45m" " MIONE " "\033[1;37;44m" " %s " "\033[0m" "\n",MIONE_VERSION);

    exit(MIONE_FAILED);
}

#endif //ERR_H
