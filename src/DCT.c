#include <math.h>
#include <stdio.h>
#include "../include/MCU.h"
#include "../include/tab_DCT.h"

#define M_PI  3.14159265358979323846

int16_t** mvt_value(uint8_t **m)
{
    int16_t** res = calloc(8, sizeof(int16_t*));
    for (uint8_t i=0; i<8; i++)
    {
        res[i] = calloc(8, sizeof(int16_t));
        for (uint8_t j = 0; j < 8; j++)
        {
            res[i][j] = m[i][j] - 128;
        }
    }
    return res;
}

int16_t calcul_dct(int16_t **m, uint8_t i, uint8_t j, uint16_t compteur)
{
    double somme = 0;
    for (uint8_t y = 0; y < 8; y++)
    {
        for (uint8_t x = 0; x < 8; x++)
        {
            int16_t tmp = m[x][y];
            somme += tmp * tab_DCT[compteur];
            compteur ++;
        }
    }
    somme = somme/4;
    if (i == 0 && j == 0){
        somme = somme/2;
    }
    else if (i==0 || j==0){
        somme = somme/sqrt(2);
    }
    return (int16_t)somme;
}

int16_t **dct(uint8_t **m)
{
    uint64_t compteur= 0;
    int16_t **res = mvt_value(m);
    int16_t **tab_final = malloc(8 * sizeof(int16_t*));
    for (uint8_t i=0; i<8; i++)
    {
        tab_final[i] = malloc(8 * sizeof(int16_t));
        for (uint8_t j = 0; j < 8; j++)
        {
            tab_final[i][j] = calcul_dct(res, i, j, compteur);
            compteur += 64;
        }
    }
    return tab_final;
}


// int main(){
//     double* tab = malloc(4096*sizeof(double));
//     uint16_t compteur = 0;
//     double val1[8];
//     double val2 = 0;
//     for (uint8_t i=0; i<8; i++)
//     {
//         for (uint8_t j = 0; j < 8; j++)
//         {
//             for (uint8_t x = 0; x < 8; x++)
//             {
//                 val1[x] = cos((2*x+1)*i*M_PI / 16);

//             }
//             for (uint8_t y = 0; y < 8; y++)
//             {
//                 val2 = cos((2*y+1)*j*M_PI / 16);
//                 for (uint8_t x = 0; x < 8; x++)
//                     {
//                         tab[compteur] =  val1[x] * val2;
//                         compteur ++;
//                     }
//             }
//         }
//     }
//     printf("%d \n", compteur);
//     for (int i = 0 ; i < compteur; i ++){
//         printf("%lf, ", tab[i]);
//     }
//     printf("\n");
//     free(tab);

// }


// int main(){ //test 
//     MCU *m = (MCU*)malloc(sizeof(MCU));
//     uint8_t **tab = (uint8_t**)malloc(8*sizeof(uint8_t*));
//     for (uint8_t i=0;i<8;i++){
//         tab[i]= (uint8_t*)malloc(8*sizeof(uint8_t));
//         for (uint8_t j=0;j<8;j++){
//             tab[i][j] = rand()%256;
//         }
//     }
//     m -> tab = tab;
//     int16_t **res_2 = dct(m);


//     for (int i=0;i<8;i++){
//         free(tab[i]);
//     }
//     free(tab);
//     free(m);

//     for (int i=0;i<8;i++){
//         for (int j=0;j<8;j++){
//             printf("%d ", res_2[i][j]);
//         }
//         printf("\n");
//     }
//     return 0;
// }

