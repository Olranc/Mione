#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int getWordType(char** var, char word) {
    *var = "\0";
    if (word == '"' || word == '\'') {
        *var = "'";
        return 1;
    }
    

    if (word == ' ') {
        *var = " ";
        return 1;
    }

    if (word == '=') {
        *var = "=";
        return 1;
    }


    for (int i = 0; i < 26; i++) {
        char a;
        a = 64 + i;

        char b;
        b = 96 + i;
        if (word == a || word == b) {
            *var = "abc123";
            return 1;
            //printf(" %c %c\n",a,b);
        }
    }

    if (word == '{' || word == '}') {
        *var = "table";
        return 1;
    }


    return 2;
};


int main() {
    FILE* file = fopen("index.mio", "r");
    char line[2048];

    if (file == NULL) {
        printf("cant open file\n");
        return 1;
    }

    // "Hello World"
    char inString = '\0';
    char nextInString = 'n';

    // $ ... @ | $ ... #
    int inFunction = 0;
    int nextInFunction = 2;

    //{x,y,z}
    int inTable = 0;
    int nextInTable = 2;

    // (x,y,z)
    int inGather = 0;
    int nextInGether = 2;

    int inNumber = 0;
    int nextImNumber = 2;

    char* lastWordType = "\0";

    char* txt = malloc(strlen("Mione") * sizeof(char));
    strcpy(txt, "Mione");

    while (fgets(line, sizeof(line), file)) { //     C
        //  printf("%s\n",line);

        inString = '\0';
        nextInString = 'n';


        int lastOne = strlen(line) - 1;

        for (int i = 0; strlen(line) > i; i++) { // C      C Ӧr
            if (i == lastOne) {
                strcat(line, " ");
            }

            char word = line[i];
            char* wordType;

            char* caseType;
            caseType = malloc((strlen("none") + 1) * sizeof(char));
            strcpy(caseType, "none");

            getWordType(&wordType, word);


            if (nextInString == 'n') { // P _ r
                if (wordType == "'") {
                    if (inString != '\0') {
                        nextInString = '\0';
                    }
                    else {
                        inString = word;
                    }
                }


            }
            else {
                inString = nextInString;
                nextInString = 'n';
            }









            if (nextInTable == 2) {
                // L
                if (wordType == "table") {
                    if (inTable == 1) {
                        nextInTable = 0;
                    }
                    else if (inTable == 0) {
                        inTable = 1;
                    }
                }


            }
            else {
                inTable = 0;
                nextInTable = 2;
            }









            //=========================================================================
            if (inTable == '\0') {

            }
            else {
                char a[] = "table";
                caseType = realloc(caseType, (strlen(a) + 1) * sizeof(char));

                //caseType = a;
                strcpy(caseType, a);
            }
            if (inString == '\0') {

            }
            else {
                char a[] = "string";

                caseType = realloc(caseType, (strlen(a) + 1) * sizeof(char));

                strcpy(caseType, a);
            }

            printf("%s %c\n", caseType, word);


            if (inString == '\0') {

            }
            else {

                wordType = "'";
            }


            if (lastWordType == wordType && i != strlen(line) - 1) { // ̫ @ 榳 Q  i ӤF
                char a[2];
                a[0] = word;
                a[1] = '\0';

                txt = realloc(txt, sizeof(char) * (strlen(a) + 1));
                strcat(txt, a);
                //printf("aaaa:%s %c\n",a,inString);
            }
            else {

                printf(" here : %s\n", txt); //

                txt = realloc(txt, sizeof(char) * (1));
                strcpy(txt, "");



                char a[2];
                a[0] = word;
                a[1] = '\0';

                txt = realloc(txt, sizeof(char) * (strlen(a) + 1));
                strcat(txt, a);
                //printf("bbbb:%s %c\n",a,inString);

            }


            lastWordType = wordType;
            //free(caseType);
            //printf("%c %c \n",word,inString);
        }
    }

    fclose(file);

    return 0;
}
