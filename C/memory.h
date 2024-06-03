void to(char **me,char**elsse,char**type);


#ifndef memory_h
#define memory_h
char*** memory = NULL;
int Type = 0;

int mSize = 0;


void lazy(char**ma,int S){
    int size = snprintf(NULL, 0, "%d", S) + 1;
    char* output = NULL;
    output= malloc(size * sizeof(char));
    sprintf(output, "%d", S);
    *ma = output;
}

void to(char **me,char**elsse,char**type){
    printf("    [TO]\n");
    //printf("%s %s for to;\n",*type,*elsse);
    if (strcmp(me[1], "0") == 0) {
        *elsse = "NULL";
        *type = "0";
    }
    else {
        if (strcmp(me[0], "VALUE") == 0) {
            printf("VAL %s\n",memory[3][0]);
            *elsse = memory[atoi(me[1]) - 1][1];
            printf("1 %s\n",me[1]); //todo 1:NULL 0:VALUE
            *type = memory[atoi(me[1]) - 1][0];
            printf("2\n");
        }
        if (strcmp(me[0], "VARIABLE") == 0) {
            printf("VAR\n");
            *elsse = memory[atoi(me[1]) - 1][2];
            printf("1\n");
            *type = memory[atoi(me[1]) - 1][1];
            printf("2\n");
        }
    }
    printf("    [TO : END]\n");
}

void cm(char** ma, char* v, int _type) {
    // memory = {   {"x",2,"sssss"}   }

    for (int i = 0; i <mSize;i++){
        if (strcmp(memory[i][0], v)==0)
        {
            lazy(ma,i+1);

            return;
        }
    }

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

    


    printf("    [MEMORY CREATED]\n");
    printf("                    [SPACENAME]:'%s'\n", memory[mSize - 1][0]);
    printf("                    [VALUETYPE]:'%s'\n", memory[mSize - 1][1]);
    printf("                    [VALUE]:'%s'\n", memory[mSize - 1][2]);
    printf("    [ADDRESS]:'%d\n", mSize);

    lazy(ma,mSize);
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


    memory[mSize - 1][0] = malloc(32);
    sprintf(memory[mSize - 1][0], "%d", _type);

    memory[mSize - 1][1] = malloc(strlen(v) + 1);
    strcpy(memory[mSize - 1][1],v);



    printf("    [MEMORY CREATED]\n");
    printf("                    [VALUETYPE]:'%s'\n", memory[mSize - 1][0]);
    printf("                    [VALUE]:'%s'\n", memory[mSize - 1][1]);
    printf("    [ADDRESS]:'%d\n", mSize);

    lazy(ma,mSize);
}

#endif /* memory_h */