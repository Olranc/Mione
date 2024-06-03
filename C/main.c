#define Mione "You owned."

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

	
	if (num >= 2) {
		if (wcscmp(cmds[1], L"o") == 0) {
			char m[256];
			WideCharToMultiByte(CP_ACP, 0, cmds[2], -1, m, sizeof(m), NULL, NULL);
            int Lines = 0;

			toBeCompileOnFile(m,&THEFILE,&Lines);
            int c_size = compile(THEFILE,Lines);
            run(&end, &endSizel,c_size,NULL,0); //run
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
			printf("\n\n\Your left made it for you.\n\n\n");
		}
		
	}
	else if (num == 1) {
        int Lines = 0;
		toBeCompileOnFile(MYFILE,&THEFILE,&Lines);
        int c_size = compile(THEFILE,Lines);
        run(&end, &endSizel,c_size,NULL,0); //run
        printf("fin size : %d\n",c_size);
        printf("Mione ,you owned.\n\n");
	}



	LocalFree(cmds);
	return 0;
}
