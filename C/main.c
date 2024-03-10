#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <Windows.h>

#include "mione.h"
#include "err.h"

int getWordType(int* var, char word) {
	*var = "\0";
	if (word == '"' || word == '\'') {
		*var = 2;
		return 1;
	}


	if (word == ' ') {
		*var = -1;
		return 1;
	}



	for (int i = 0; i < 26; i++) {
		char a;
		a = 65 + i;
		char b;
		b = 97 + i;

	  
		if (word == a || word == b) {
			*var = 6;
			return 1;
		}
		
	}

	for (int i = 0; i < 10; i++) {
		char aw[5];
		sprintf(aw, "%d", i);

		if (aw) {
			if (word == aw[0]) {
				*var = 5;
				return 1;
			}
		}
	}

	if (word == '{') {
		*var = 3;
		return 1;
	}
	if (word == '}') {
		*var = 8;
		return 1;
	}


	if (word == '$') {
		*var = 4;
		return 1;
	}
	if (word == '@' || word == '#') {
		*var = 9;
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


	while (fgets(line, sizeof(line), file) != NULL) { //     C
		//  printf("%s\n",line);

		int lastOne = strlen(line) - 1;

		for (int i = 0; strlen(line) > i; i++) { // C
			if (i == lastOne) {
				strcat(line, " ");
			}

			char word = line[i];
			int wordType = 1;
			
			getWordType(&wordType, word);

			mione(word, wordType);

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
	}
	else if (num == 1) {
		OPEN("index.mio");
		printf("a... you might find page is here => 'mione home'\n\n");
	}



	LocalFree(cmds);
	return 0;
}

