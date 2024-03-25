#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char ***memory = NULL;
int mSize = 0;

#ifndef memory_h
#define memory_h

void cm(char **ma, char *v, int _type) {
    mSize++;
    if (memory) {
        memory = realloc(memory, sizeof(char**) * mSize);
    } else {
        memory = malloc(sizeof(char**));
    }
    memory[mSize-1] = malloc(sizeof(char*) * 2);
    memory[mSize-1][0] = malloc(strlen(v) + 1);
    sprintf(memory[mSize-1][0], "%d", _type);
    memory[mSize-1][1] = malloc(strlen(v) + 1);
    strcpy(memory[mSize-1][1], v);

    int size = snprintf(NULL, 0, "%d", mSize) + 1;

    char *output = malloc(size * sizeof(char));
    sprintf(output, "%d", mSize);
    *ma = output;
}

#endif
