#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <Windows.h>

#include "mione.h"

char* def1;
char* def2;

int getWordType(char** var, char word) {
    *var = "\0";
    if (word == '"' || word == '\'') {
        *var = "'";
        return 1;
    }


    if (word == ' '||word == '\n') {
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


    if (word == '$' || word == '@' || word == '#') {
        *var = "function";
        return 1;
    }


    return 2;
};

int OPEN(char* fileName) {
    FILE* file = fopen(fileName, "r");
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

    char* lastWordType = "abc123";

    char* txt = malloc(1 * sizeof(char));
    strcpy(txt, " ");

    while (fgets(line, sizeof(line), file) != NULL) { //     C
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

            char* caseType = malloc(0 * sizeof(char));
            caseType = realloc(caseType, strlen("none") * sizeof(char));
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
            if (inString == '\0') {

            }
            else {
                char a[] = "string";

                caseType = realloc(caseType, (strlen(a) + 1) * sizeof(char));

                strcpy(caseType, a);
                wordType = "'";
            }
            if (inTable == '\0') {

            }
            else {
                char a[] = "table";
                caseType = realloc(caseType, (strlen(a) + 1) * sizeof(char));

                //caseType = a;
                strcpy(caseType, a);
                wordType = "table";
            }


            if (lastWordType == wordType && i != strlen(line) - 1) {
                printf("%s %c\n",wordType,word);
            }
            else {

                mione(word,wordType);


            }


            lastWordType = wordType;
        }
    }

    fclose(file);
    return 0;
}

int main() {
    LPWSTR* cmds;
    int num;
    cmds = CommandLineToArgvW(GetCommandLineW(), &num);
    char m[256];

    if (num >= 2) {
        if (wcscmp(cmds[1], L"o") == 0) {
            WideCharToMultiByte(CP_ACP, 0, cmds[2], -1, m, sizeof(m), NULL, NULL);

            OPEN(m);
        }

        if (wcscmp(cmds[1], L"home") == 0) {
            printf("Hello, World!\n\n");
            printf("==================================================================\n");
            printf("          ____                                                \n");
            printf("        ,'  , `.                                              \n");
            printf("     ,-+-,.' _ |   ,--,                                       \n");
            printf("  ,-+-. ;   , || ,--.'|       ,---.         ,---,             \n");
            printf(" ,--.'|'   |  ;| |  |,       '   ,'\    ,-+-. /  |            \n");
            printf("|   |  ,', |  ': `--'_      /   /   |  ,--.'|'   |    ,---.   \n");
            printf("|   | /  | |  || ,' ,'|    .   ; ,. : |   |  ,'' |   /     \  \n");
            printf("'   | :  | :  |, '  | |    '   | |: : |   | /  | |  /    /  | \n");
            printf(";   . |  ; |--'  |  | :    '   | .; : |   | |  | | .    ' / | \n");
            printf("|   : |  | ,     '  : |__  |   :    | |   | |  |/  '   ;   /| \n");
            printf("|   : '  |/      |  | '.'|  \   \  /  |   | |--'   '   |  / | \n");
            printf(";   | |`-'       ;  :    ;   `----'   |   |/       |   :    | \n");
            printf("|   ;/           |  ,   /             '---'         \   \  /  \n");
            printf("'---'             ---`-'                             `----'   \n");
            printf("==================================================================");
        }
    }
    else if (num == 1) {
        OPEN("index.mio");
        printf("a... you might find page is here => 'mione home'\n\n");
    }



    LocalFree(cmds);
    return 0;
}

