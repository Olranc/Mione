//
// Created by calle on 24-7-26.
//

const int HEAD,PROMPT,SYMBOL,VARIABLE,VALUE;

char*Heads[];
char*Prompts[];
char*Symbols[];

int returnType(char* c);

#ifndef HPSVV_H
#define HPSVV_H

const int HEAD = 1;
const int PROMPT = 2;
const int SYMBOL = 3;
const int VARIABLE = 4;
const int VALUE = 5;

char *Heads[] = {
    "set"
};
char *Prompts[] = {
    "="
};
char *Symbols[] = {
    "+"
};

#endif //HPSVV_H
