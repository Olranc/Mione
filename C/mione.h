#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "prerr.h"


int getWordType(int* var, char word) {
	*var = 1;
	if (word == '"' || word == '\'') {
		*var = 2;
		return 1;
	}


	if (word == ' ') {
		*var = -1;
		return 1;
	}

	if (word == '=') {
		*var = 7;
		return 1;
	}

	if (word == ',') {
		*var = 11;
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


	if (word == '@') {
		*var = 4;
		return 1;
	}
	if (word == '$') {
		*var = 9;
		return 1;
	}
	if (word == '#') {
		*var = 10;
		return 1;
	}

	if (word == '\n') {
		*var = 1;
		return 1;
	}
	

	return 2;
};
int Line = 0;

int	nextWordType = 0;
int	lastWordType = 6;
int wordType = 1;

int lvlStratLine = 0;
int lvl = 0;
int canCount = 1;
int nextCanCount = 0;


int canWrite = 1;
int nextCanWrite = 0;

int OPEN(char* fileName) {

	char* txt = malloc(sizeof(char) * 2);
	strcpy(txt,"\0");
	FILE* file = fopen(fileName, "r");
	char line[2048];

	if (file == NULL) {
		printf("cant open file\n");
		return 1;
	}
	
	while (fgets(line, sizeof(line), file) != NULL) { //     C
		Line++;
		//  printf("%s\n",line);

		int lastOne = strlen(line) - 1;

		for (int i = 0; strlen(line) > i; i++) { // C
			if (i == lastOne) {
				strcat(line, " ");
			}

			char word = line[i];
			int checkType = 1;
			getWordType(&checkType, word);

			//====================================================
			if (nextCanWrite) {
				canWrite = nextCanWrite;
				nextCanWrite = 0;
			}

			if (nextCanCount) {
				canCount = nextCanCount;
				nextCanCount = 0;
			}

			// CHECKTYPE:
			// -1:空格/換行 1:無 2:字串開頭 3:表單開頭 4:函數結束 5:數字 6:英文字母 7:等號 8:表單結束 9:函數開頭1 10:函數開頭2 11:斷句

			// WORDTYPE:
			// -1:空格/換行 1:無 2:字串 3:表單 4:函數 5:數字 6:英文字母 7:等號 8:執行式 9:斷句

			if (nextWordType) { 
				wordType = nextWordType;
				nextWordType = 0;
			}
			else {
				if (checkType == 2) { // STRING 字串
					if (lastWordType == 2) {
						nextCanWrite = 1;
					}
					else {
						if (canWrite == 1) {
							wordType = 2;
							canWrite = 0;
						}

						
					}

					if (canCount) {
						canCount = 0;
					}
					else {
						nextCanCount = 1;
					}
				}

				if (checkType == 3) { // TABLE 表單
					if (canWrite == 1) {
						wordType = 3;
						canWrite = 0;

						if (canCount) {
							if (lvlStratLine) {}
							else {
								lvlStratLine = Line;
							}
							lvl++;
						}
						
					}
					else {
						if (lastWordType == 3) {
							if (canCount) {
								lvl++;
							}
						}
					}
					
				}

				if (checkType == 9) { // FUNCTION 函數
					if (canWrite == 1) {
						wordType = 4;
						canWrite = 0;

						if (canCount) {
							if (lvlStratLine) {}
							else {
								lvlStratLine = Line;
							}
							lvl++;
						}
					}
					else {
						if (lastWordType == 4 || lastWordType == 8) {
							if (canCount) {
								lvl++;
							}
						}
					}
					
				}

				if (checkType == 10) { // FUNCTION 函數
					if (canWrite == 1) {
						wordType = 8;
						canWrite = 0;

						if (canCount) {
							if (lvlStratLine) {}
							else {
								lvlStratLine = Line;
							}
							lvl++;
						}
					}
					else {
						if (lastWordType == 4 || lastWordType == 8) {
							if (canCount) {
								lvl++;
							}
						}
					}

				}

				if (checkType == 5) {
					if (canWrite == 1) {
						wordType = 5;
					}
				}

				if (checkType == 6) {
					if (canWrite == 1) {
						wordType = 6;
					}
				}

				if (checkType == 7) {
					if (canWrite == 1) {
						wordType = 7;
					}
				}

				if (checkType == 8) { // TABLE 表單
					if (lastWordType == 3) {
						
						if (canCount) {
							lvl--;
						}
						if (lvl) {}
						else {
							wordType = 3;
							nextCanWrite = 1;

							lvlStratLine = 0;
						}
						
					}
				}

				if (checkType == 4) {
					if (lastWordType == 4 || lastWordType == 8) {
						if (canCount) {
							lvl--;
						}
						if (lvl) {}
						else {
							if (lastWordType == 4) {
								wordType = 4;
							}
							else {
								wordType = 8;
							}
							
							nextCanWrite = 1;

							lvlStratLine = 0;
						}
					}
				}

				if (checkType == -1) {
					if (canWrite == 1) {
						wordType = -1;
					}
				}

				if (checkType == 1) {
					if (canWrite == 1) {
						wordType = 1;
					}
				}

				if (checkType == 11) {
					if (canWrite == 1) {
						wordType = 11;
					}
				}
			}

			
			//====================================================
			if (wordType == lastWordType) {
				int len = strlen(txt);
				txt = realloc(txt, sizeof(char) * (len + 1+1));
				txt[len] = word;
				txt[len+1] = '\0';
			}
			else {
			
				//here
				printf("%s\n", txt);

				free(txt);

				txt = malloc(sizeof(char) * (1 + 1));
				txt[0] = word;
				txt[1] = '\0';
			}


			
			printf("'%d' '%c' '%d'\n", wordType,word,lvl);
			lastWordType = wordType;
		}


	}

	if (lvlStratLine) {
		prerr(lvlStratLine, "表單或函數尚未完成**結束標示**。",1);
	}
	



	fclose(file);
	return 0;
}



#ifndef mione_h
#define mione_h
int OPEN(char* fileName);

#endif

