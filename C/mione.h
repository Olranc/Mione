#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
	if (word == '@') {
		*var = 9;
		return 1;
	}
	if (word == '#') {
		*var = 10;
		return 1;
	}


	return 2;
};

int canWrite = 1;
int nextCanWrite = 0;

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

			if () {

			}

			getWordType(&wordType, word);
			printf("%d %c\n",wordType,word);
		}


	}





	fclose(file);
	return 0;
}



#ifndef mione_h
#define mione_h
int OPEN(char* fileName);

#endif

