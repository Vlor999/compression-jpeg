#include <math.h>
#include <stdio.h>
#include "../include/MCU.h"


#define M_PI  3.14159265358979323846

int16_t calcul_dct(MCU *m, uint8_t i, uint8_t j)
{
    double somme = 0;
    for (uint8_t x = 0; x < 8; x++)
    {
        for (uint8_t y = 0; y < 8; y++)
        {
            int16_t tmp = (m -> tab)[x][y] - 128;
            somme += tmp*cos((2*x+1)*i*M_PI / 16) * cos((2*y+1)*j*M_PI / 16);
        }
    }
    somme = somme/4;
    if (i == 0 && j == 0){
        somme = somme/2;
    }
    else if (i==0 || j==0){
        somme = somme/sqrt(2);
    }
    else{
        somme = somme;
    }

    return (int16_t)somme;
    
}

int16_t **dct(MCU *m)
{
    int16_t **res = (int16_t**)malloc(8*sizeof(int16_t*));
    for (uint8_t i=0; i<8; i++)
    {
        res[i] = (int16_t*)malloc(8*sizeof(int16_t));
        for (uint8_t j = 0; j < 8; j++)
        {
            res[i][j] = calcul_dct(m, i, j);
        }
    }
    return res;
}

// int main(){ //test 
//     Mcu *m = (Mcu*)malloc(sizeof(Mcu));
//     uint8_t **tab = (uint8_t**)malloc(8*sizeof(uint8_t*));
//     for (uint8_t i=0;i<8;i++){
//         tab[i]= (uint8_t*)malloc(8*sizeof(uint8_t));
//         for (uint8_t j=0;j<8;j++){
//             tab[i][j] = rand()%256;
//         }
//     }
//     m -> tab = tab;
//     uint16_t **res = dct(m);


//     for (int i=0;i<8;i++){
//         free(tab[i]);
//     }
//     free(tab);
//     free(m);

//     for (int i=0;i<8;i++){
//         for (int j=0;j<8;j++){
//             printf("%f ",res[i][j]);
//         }
//         printf("\n");
//     }
//     return 0;
// }

