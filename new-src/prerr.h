//
// Created by calle on 24-7-26.
//
void prerr(const char* reason,const int errcode,const char line);

#ifndef PRERR_H
#define PRERR_H

void prerr(const char* reason,const int errcode,const char line)
{
    printf("\nError: %s\nLine: %d\nError code: %d\n",reason,line,errcode);
    exit(errcode);
}

#endif //PRERR_H
