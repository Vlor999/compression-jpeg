#include <math.h>
#include <stdio.h>
#include "MCU.h"

#define M_PI  3.14159265358979323846

double calcul_dct(Mcu *m, uint8_t i, uint8_t j){
    double somme = 0;
    for (uint8_t x=0;x<8;x++){
        for (uint8_t y=0;y<8;y++){
            int8_t tmp = (m -> tab)[x][y] - 128;
            somme += tmp*cos((2*x+1)*i*M_PI/16)*cos((2*y+1)*j*M_PI/16);
        }
    }
    somme = somme/4;
    if (i == 0 && j == 0){
        return somme/2;
    }
    else if (i==0 || j==0){
        return somme/sqrt(2);
    }
    else{
        return somme;
    }
}

double **dct(Mcu *m){ //COMMENT IMPLEMENTER ??
    double **res = (double**)malloc(8*sizeof(double*));
    for (uint8_t i=0;i<8;i++){
        res[i]=(double*)malloc(8*sizeof(double));
        for (uint8_t j=0;j<8;j++){
            res[i][j] = calcul_dct(m,i,j);
            printf("%f ",res[i][j]);
        }
    }
    return res;
}

int main(){ //test 
    Mcu *m = (Mcu*)malloc(sizeof(Mcu));
    uint8_t **tab = (uint8_t**)malloc(8*sizeof(uint8_t*));
    for (uint8_t i=0;i<8;i++){
        tab[i]= (uint8_t*)malloc(8*sizeof(uint8_t));
        for (uint8_t j=0;j<8;j++){
            tab[i][j] = rand()%256;
        }
    }
    m -> tab = tab;
    double **res = dct(m);


    for (int i=0;i<8;i++){
        free(tab[i]);
    }
    free(tab);
    free(m);

    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            printf("%f ",res[i][j]);
        }
        printf("\n");
    }
    return 0;
}