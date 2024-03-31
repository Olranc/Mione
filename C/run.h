#ifndef run_h
#define run_h

int the_size = 0;


int* everyLines;
int nowTraget = 0;
int soNowLine = 1;

char*** MIO;

int Rut = 0;
char*** Runthions;





int run() {
	char**** c = Rut ? &Runthions : &MIO;
	

	for (int i = 0; i < the_size; i++) {
		printf("%s %s \n", (*c)[i][0], (*c)[i][1]);
		if (i+1 == everyLines[nowTraget] && sizeof(everyLines)/sizeof(int)+1 != nowTraget) {
			
			nowTraget++;
			soNowLine++;
			printf("現在是第%d行\n", soNowLine);
		}
	}
};


#endif // !run_h
