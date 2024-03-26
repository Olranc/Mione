#include <stdio.h>
#include "verson.h"

int prerr(int line, char* msg, int errCode) {
	printf("錯誤項目開頭行數：%d\n錯誤輔助說明：%s \n", line, msg);
	printf("	Mione版本：%s\n", mione_verson);
	printf("	錯誤代碼：'%d'\n", errCode);
	return 1;
}