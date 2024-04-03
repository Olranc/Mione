#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char*** memory = NULL;
int Type = 0;

int mSize = 0;

#ifndef memory_h
#define memory_h

void cm(char** ma, char* v, int _type) {
    // memory = {   {"x",2,"sssss"}   }
    mSize++;
    if (memory) {
        memory = realloc(memory, sizeof(char**) * mSize);
    }
    else {
        memory = malloc(sizeof(char**));
    }

    memory[mSize - 1] = malloc(sizeof(char*) * 3);




    memory[mSize - 1][0] = malloc(strlen(v) + 1);
    strcpy(memory[mSize - 1][0], v);

    memory[mSize - 1][1] = malloc(strlen("1") + 1);
    strcpy(memory[mSize - 1][1], "1");
    //sprintf(memory[mSize - 1][0], "%d", _type);

    memory[mSize - 1][2] = malloc(strlen("NULL") + 1);
    strcpy(memory[mSize - 1][2], "NULL");

    


    //printf("    [MEMORY CREATED]\n");
    //printf("                    [SPACENAME]:'%s'\n", memory[mSize - 1][0]);
    //printf("                    [VALUETYPE]:'%s'\n", memory[mSize - 1][1]);
    //printf("                    [VALUE]:'%s'\n", memory[mSize - 1][2]);
    //printf("    [ADDRESS]:'%d\n", mSize);

    int size = snprintf(NULL, 0, "%d", mSize) + 1;
    char* output = NULL;
     output= malloc(size * sizeof(char));
    sprintf(output, "%d", mSize);
    *ma = output;
}

void cm_v(char ** ma,int _type,char* v) { //
    mSize++;
    if (memory) {
        memory = realloc(memory, sizeof(char**) * mSize);
    }
    else {
        memory = malloc(sizeof(char**));
    }

    memory[mSize - 1] = malloc(sizeof(char*) * 2);


    memory[mSize - 1][0] = malloc(32); //�̰��u�䴩 31�Ӧ��
    sprintf(memory[mSize - 1][0], "%d", _type);

    memory[mSize - 1][1] = malloc(strlen(v) + 1);
    strcpy(memory[mSize - 1][1],v);



    //printf("    [MEMORY CREATED]\n");
    //printf("                    [VALUETYPE]:'%s'\n", memory[mSize - 1][0]);
    //printf("                    [VALUE]:'%s'\n", memory[mSize - 1][1]);
    //printf("    [ADDRESS]:'%d\n", mSize);

    int size = snprintf(NULL, 0, "%d", mSize) + 1;

    char* output = NULL;
    output= malloc(size * sizeof(char));
    sprintf(output, "%d", mSize);
    *ma = output;
}

void rtm(char**** c) {
    *c = memory;
}

#endif
