#define Mione "You owned."
//ᣌ⪥
//  ᴥ
#define _CRT_SECURE_NO_WARNINGS
#define _WINDOWS

#define MYFILE "index.mio" //D:\\

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <Windows.h>

#include "mione.h"
#include "version.h"


void ColorText() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

int main() {
    ColorText();
	LPWSTR* cmds;
	int num;
	cmds = CommandLineToArgvW(GetCommandLineW(), &num);

    char *** end = NULL;
    int endSizel = 0;

    char ** THEFILE = NULL;
    char ***MIO=NULL;

	
	if (num >= 2) {
		if (wcscmp(cmds[1], L"o") == 0) {
			char m[256];
			WideCharToMultiByte(CP_ACP, 0, cmds[2], -1, m, sizeof(m), NULL, NULL);
            int Lines = 0;

            int NL = 0;
            int *EveryLine = NULL ;
			toBeCompileOnFile(m,&THEFILE,&Lines);
            memory=malloc(sizeof(char***)*1);
            memory[0] = NULL;
            mSize = malloc(sizeof(int)*1);
            mSize[0] = 0;

            int c_size = compile(THEFILE,Lines,&MIO,0,&NL,&EveryLine);
            run(&end, &endSizel,c_size,NULL,0,MIO,0,NL,EveryLine); //run

            if (endSizel > 0){
                if (strcmp(end[0][0],"ERR") == 0){
                    prerr(atoi(end[0][3]),end[0][2],atoi(end[0][1]));
                }
            }
		}

		if (wcscmp(cmds[1], L"mione") == 0) {

			printf("==================================================================\n");
			printf("          ____                                                \n");
			printf("        ,'  , `.                                              \n");
			printf("     ,-+-,.' _ |   ,--,                                       \n");
			printf("  ,-+-. ;   , || ,--.'|       ,---.         ,---,             \n");
			printf(" ,--.'|'   |  ;| |  |,       '   ,'\\    ,-+-. /  |            \n");
			printf("|   |  ,', |  ': `--'_      /   /   |  ,--.'|'   |    ,---.   \n");
			printf("|   | /  | |  || ,' ,'|    .   ; ,. : |   |  ,'' |   /     \\  \n");
			printf("'   | :  | :  |, '  | |    '   | |: : |   | /  | |  /    /  | \n");
			printf(";   . |  ; |--'  |  | :    '   | .; : |   | |  | | .    ' / | \n");
			printf("|   : |  | ,     '  : |__  |   :    | |   | |  |/  '   ;   /| \n");
			printf("|   : '  |/      |  | '.'|  \\   \\  /  |   | |--'   '   |  / | \n");
			printf(";   | |`-'       ;  :    ;   `----'   |   |/       |   :    | \n");
			printf("|   ;/           |  ,   /             '---'         \\   \\  /  \n");
			printf("'---'             ---`-'                             `----'   \n");
			printf("==================================================================");
		}
		if (wcscmp(cmds[1], L"version") == 0) {
			printf("Mione version:%s\n\n\n", mione_version);
		}
        if (wcscmp(cmds[1], L"open_source") == 0){
            printf("\n\n\nMione : %s \n\n\n", "https://github.com/Mioprety/Mione");
        }
		if (wcscmp(cmds[1], L"mxh") == 0) {
			printf("\n\nYour left made it for you.\n\n\n");
		}
		
	}
	else if (num == 1) {

        int Lines = 0;

        int NL= 0;
        int *EveryLine =NULL ;
		toBeCompileOnFile(MYFILE,&THEFILE,&Lines);
        memory=malloc(sizeof(char***)*1);
        memory[0] = NULL;
        mSize = malloc(sizeof(int)*1);
        mSize[0] = 0;

        int c_size = compile(THEFILE,Lines,&MIO,0,&NL,&EveryLine);
        run(&end, &endSizel,c_size,NULL,0,MIO,0,NL,EveryLine); //run

        if (endSizel > 0){
            if (strcmp(end[0][0],"ERR") == 0){
                printf("OH %s\n",end[0][3]);
                prerr(atoi(end[0][3]),end[0][2],atoi(end[0][1]));
            }
        }

        printf("\n\nMione ,you owned.\n\n");
	}



	LocalFree(cmds);
	return 0;
}
