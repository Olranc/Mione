int* mSize;
char**** memory;
void to(char **me,char**value,char**type,int MEMORY_GROUP );


#ifndef memory_h
#define memory_h
char**** memory = NULL;


void lazy(char**ma,int S){
    int size = snprintf(NULL, 0, "%d", S) + 1;
    char* output = NULL;
    output= malloc(size * sizeof(char));
    sprintf(output, "%d", S);
    *ma = output;
}

void to(char **me,char**value,char**type,int MEMORY_GROUP){
    if (strcmp(me[1], "0") == 0) {
        *value = "NULL";
        *type = "0";
    }
    else {

        if (strcmp(me[0], "VALUE") == 0) {
            *value = memory[MEMORY_GROUP][atoi(me[1]) - 1][1];
            *type = memory[MEMORY_GROUP][atoi(me[1]) - 1][0];
        }
        if (strcmp(me[0], "VARIABLE") == 0) {
            *value = memory[MEMORY_GROUP][atoi(me[1]) - 1][2];
            *type = memory[MEMORY_GROUP][atoi(me[1]) - 1][1];
        }
    }
}

void cm(char** ma, char* v, int _type,int MEMORY_GROUP ) {
    // memory[MEMORY_GROUP] = {   {"x",2,"sssss"}   }
    for (int i = 0; i <mSize[MEMORY_GROUP];i++){
        if (strcmp(memory[MEMORY_GROUP][i][0], v)==0)
        {
            lazy(ma,i+1);

            return;
        }
    }

    mSize[MEMORY_GROUP]++;
    if (memory[MEMORY_GROUP]) {
        memory[MEMORY_GROUP] = realloc(memory[MEMORY_GROUP], sizeof(char**) * mSize[MEMORY_GROUP]);
    }
    else {
        memory[MEMORY_GROUP] = malloc(sizeof(char**));
    }
    memory[MEMORY_GROUP][mSize[MEMORY_GROUP] - 1] = malloc(sizeof(char*) * 3);




    memory[MEMORY_GROUP][mSize[MEMORY_GROUP] - 1][0] = malloc(strlen(v) + 1);
    strcpy(memory[MEMORY_GROUP][mSize[MEMORY_GROUP] - 1][0], v);

    memory[MEMORY_GROUP][mSize[MEMORY_GROUP] - 1][1] = malloc(strlen("1") + 1);
    strcpy(memory[MEMORY_GROUP][mSize[MEMORY_GROUP] - 1][1], "1");
    //sprintf(memory[MEMORY_GROUP][mSize[MEMORY_GROUP] - 1][0], "%d", _type);

    memory[MEMORY_GROUP][mSize[MEMORY_GROUP] - 1][2] = malloc(strlen("NULL") + 1);
    strcpy(memory[MEMORY_GROUP][mSize[MEMORY_GROUP] - 1][2], "NULL");




    printf("    [MEMORY CREATED]\n");
    printf("                    [SPACENAME]:'%s'\n", memory[MEMORY_GROUP][mSize[MEMORY_GROUP] - 1][0]);
    printf("                    [VALUETYPE]:'%s'\n", memory[MEMORY_GROUP][mSize[MEMORY_GROUP] - 1][1]);
    printf("                    [VALUE]:'%s'\n", memory[MEMORY_GROUP][mSize[MEMORY_GROUP] - 1][2]);
    printf("                    [GROUP]:'%d'\n", MEMORY_GROUP);

    printf("    [ADDRESS]:'%d\n", mSize[MEMORY_GROUP]);

    lazy(ma,mSize[MEMORY_GROUP]);
}

void cm_v(char ** ma,int _type,char* v,int MEMORY_GROUP ) { //
    mSize[MEMORY_GROUP]++;

    if (memory[MEMORY_GROUP]) {
        memory[MEMORY_GROUP] = realloc(memory[MEMORY_GROUP], sizeof(char**) * mSize[MEMORY_GROUP]);
    }
    else {
        memory[MEMORY_GROUP] = malloc(sizeof(char**));
    }

    memory[MEMORY_GROUP][mSize[MEMORY_GROUP] - 1] = malloc(sizeof(char*) * 2);


    memory[MEMORY_GROUP][mSize[MEMORY_GROUP] - 1][0] = malloc(32);
    sprintf(memory[MEMORY_GROUP][mSize[MEMORY_GROUP] - 1][0], "%d", _type);

    memory[MEMORY_GROUP][mSize[MEMORY_GROUP] - 1][1] = malloc(strlen(v) + 1);
    strcpy(memory[MEMORY_GROUP][mSize[MEMORY_GROUP] - 1][1],v);



    printf("    [MEMORY CREATED]\n");
    printf("                    [VALUETYPE]:'%s'\n", memory[MEMORY_GROUP][mSize[MEMORY_GROUP] - 1][0]);
    printf("                    [VALUE]:'%s'\n", memory[MEMORY_GROUP][mSize[MEMORY_GROUP] - 1][1]);
    printf("                    [GROUP]:'%d'\n", MEMORY_GROUP);
    printf("    [ADDRESS]:'%d\n", mSize[MEMORY_GROUP]);

    lazy(ma,mSize[MEMORY_GROUP]);
}

#endif /* memory_h */