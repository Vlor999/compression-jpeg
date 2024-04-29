#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Fonction qui prend en paramètre une matrice 8x8 et qui retourne un tableau 1D de taille 64
double* zigzag_matrice(double** matrice)
{
    double* zigzag = malloc(64 * sizeof(double));
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


int main(void)
{
    double** matrice = (double**)malloc(8 * sizeof(double*));
    for (int i = 0; i < 8; i++)
    {
        matrice[i] = (double*)malloc(8 * sizeof(double));
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            matrice[i][j] = i * 8 + j;
            printf("%f ", matrice[i][j]);
        }
        printf("\n");
    }
    double* zigzag = zigzag_matrice(matrice);
    for (int i = 0; i < 64; i++)
    {
        printf("%f\n", zigzag[i]);
    }
    return 0;
}