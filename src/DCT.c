#include <math.h>
#include <stdio.h>
#include "../include/MCU.h"
#include "../include/tab_DCT.h"
#include "../include/conversionRGB.h"

#define M_PI  3.14159265358979323846
#define RACINE 0.70710678118

int16_t calcul_dct(uint8_t **m, uint8_t i, uint8_t j, uint16_t compteur)
{
    double somme = 0;
    for (uint8_t y = 0; y < MCU_TAILLE; y++)
    {
        for (uint8_t x = 0; x < MCU_TAILLE; x++)
        {
            int16_t tmp = m[x][y] - 128;
            somme += tmp * tab_DCT[compteur];
            compteur++;
        }
    }
    somme = somme/4;
    if (i == 0 && j == 0){
        somme = somme/2;
    }
    else if (i==0 || j==0){
        somme = somme * RACINE;
    }
    return (int16_t)somme;
}

int16_t **dct(uint8_t **m)
{
    uint64_t compteur = 0;
    int16_t **tab_final = malloc(MCU_TAILLE * sizeof(int16_t*));
    for (uint8_t i = 0; i < MCU_TAILLE; i++)
    {
        tab_final[i] = malloc(MCU_TAILLE * sizeof(int16_t));
        for (uint8_t j = 0; j < MCU_TAILLE; j++)
        {
            tab_final[i][j] = calcul_dct(m, i, j, compteur);
            compteur += MCU_TAILLE * MCU_TAILLE;
        }
    }
    return tab_final;
}
