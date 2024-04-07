//
// Created by chenn on 2024/4/7.
//

#ifndef VV_h
#define VV_h

int VV(char*** _while,int _whileSize){
    printf("    [NEW V/V]\n");
    for (int i = 0; i < _whileSize; i++) {
        printf("%s %s\n",_while[i][0],_while[i][1]);

    }
    printf("    [END V/V]\n\n");
}

#endif //MIONE_VV_H
