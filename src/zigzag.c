#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/conversionRGB.h"

// Fonction qui prend en paramètre une matrice 8x8 et qui retourne un tableau 1D de taille 64
int16_t* zigzag_matrice(int16_t** matrice)
{
    int16_t* zigzag = malloc(MCU_TAILLE * MCU_TAILLE * sizeof(int16_t));
    int l = 0;
    int c = 0;
    int coeff_dire = 1;
    int compteur = 0;
    while (l + c <= 14)
    {
        int n = abs(l - c); //permet de trouver la diagonale sur laquelle on se trouve
        int nb = n; //nombre d'éléments sur la diagonale
        for (int i = 0; i <= nb; i++)
        {
            zigzag[compteur] = matrice[l][c]; //on ajoute l'élément à la liste
            if (coeff_dire == 1 && i != nb) // ici on descend sur la diagonale, on fait attention au effet de bord
            {
                l = l - 1;
                c = c + 1;
            }
            else if (coeff_dire == -1 && i != nb) // idem mais on monte
            {
                l = l + 1;
                c = c - 1;
            }
            compteur += 1;
        }
        if (coeff_dire == 1) // Si on descendais alors on va monter et on change les valeurs en fonction de la moitié dans laquelle nous sommes
        {
            if (c == 7)
            {
                l += 1;
            }
            else
            {
                c += 1;
            }
            coeff_dire = -1;
        }
        else // même idée ici
        {
            if (l == 7)
            {
                c += 1;
            }
            else
            {
                l += 1;
            }
            coeff_dire = 1;
        }
    }
    return zigzag;
}

int16_t* zigzag_matrice1(int16_t** matrice) 
{   /*
    Fonction qui prend en paramètre une matrice 8x8 et qui retourne un tableau 1D de taille 64.
    Cette version est plus effcicace que le précédente car il n'y a aucune condition mais beaucoup plus grande. 
    Nous avons obtenu cette version en observant les indices de la matrice 8x8 et en les mettant dans l'ordre du zigzag. Ceci grace à la fonction précédente.
    */
    int16_t* zigzag = malloc(MCU_TAILLE * MCU_TAILLE * sizeof(int16_t));
    zigzag[0] = matrice[0][0];
    zigzag[1] = matrice[0][1];
    zigzag[2] = matrice[1][0];
    zigzag[3] = matrice[2][0];
    zigzag[4] = matrice[1][1];
    zigzag[5] = matrice[0][2];
    zigzag[6] = matrice[0][3];
    zigzag[7] = matrice[1][2];
    zigzag[8] = matrice[2][1];
    zigzag[9] = matrice[3][0];
    zigzag[10] = matrice[4][0];
    zigzag[11] = matrice[3][1];
    zigzag[12] = matrice[2][2];
    zigzag[13] = matrice[1][3];
    zigzag[14] = matrice[0][4];
    zigzag[15] = matrice[0][5];
    zigzag[16] = matrice[1][4];
    zigzag[17] = matrice[2][3];
    zigzag[18] = matrice[3][2];
    zigzag[19] = matrice[4][1];
    zigzag[20] = matrice[5][0];
    zigzag[21] = matrice[6][0];
    zigzag[22] = matrice[5][1];
    zigzag[23] = matrice[4][2];
    zigzag[24] = matrice[3][3];
    zigzag[25] = matrice[2][4];
    zigzag[26] = matrice[1][5];
    zigzag[27] = matrice[0][6];
    zigzag[28] = matrice[0][7];
    zigzag[29] = matrice[1][6];
    zigzag[30] = matrice[2][5];
    zigzag[31] = matrice[3][4];
    zigzag[32] = matrice[4][3];
    zigzag[33] = matrice[5][2];
    zigzag[34] = matrice[6][1];
    zigzag[35] = matrice[7][0];
    zigzag[36] = matrice[7][1];
    zigzag[37] = matrice[6][2];
    zigzag[38] = matrice[5][3];
    zigzag[39] = matrice[4][4];
    zigzag[40] = matrice[3][5];
    zigzag[41] = matrice[2][6];
    zigzag[42] = matrice[1][7];
    zigzag[43] = matrice[2][7];
    zigzag[44] = matrice[3][6];
    zigzag[45] = matrice[4][5];
    zigzag[46] = matrice[5][4];
    zigzag[47] = matrice[6][3];
    zigzag[48] = matrice[7][2];
    zigzag[49] = matrice[7][3];
    zigzag[50] = matrice[6][4];
    zigzag[51] = matrice[5][5];
    zigzag[52] = matrice[4][6];
    zigzag[53] = matrice[3][7];
    zigzag[54] = matrice[4][7];
    zigzag[55] = matrice[5][6];
    zigzag[56] = matrice[6][5];
    zigzag[57] = matrice[7][4];
    zigzag[58] = matrice[7][5];
    zigzag[59] = matrice[6][6];
    zigzag[60] = matrice[5][7];
    zigzag[61] = matrice[6][7];
    zigzag[62] = matrice[7][6];
    zigzag[63] = matrice[7][7];
    return zigzag;
}
