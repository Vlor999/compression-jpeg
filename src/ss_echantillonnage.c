#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../include/conversionRGB.h"
#include "../include/recup_v2.h"


Triplet_YCbCr** ss_echantillonnage422(Triplet_YCbCr** tableau, uint32_t lignes, uint32_t col){
    Triplet_YCbCr** tab_echantillonnee = malloc(lignes * sizeof(Triplet_YCbCr*));
    float valeur_Cb;
    float valeur_Cr;
    for (uint32_t i = 0; i < lignes; i++)
    {
        tab_echantillonnee[i] = malloc(col * sizeof(Triplet_YCbCr));
        for (uint32_t j = 0; j < col; j++)
        {
            if (j%2 == 0){
                valeur_Cb = tableau[i][j].Cb;
                valeur_Cr = tableau[i][j].Cr;
                tab_echantillonnee[i][j].Cb = 0;
                tab_echantillonnee[i][j].Cr = 0;
                tab_echantillonnee[i][j].Y = tableau[i][j].Y;
            }
            else if (j > 0){
                tab_echantillonnee[i][j].Cb = (tableau[i][j].Cb + valeur_Cb)/2 ;
                tab_echantillonnee[i][j].Cr = (tableau[i][j].Cr + valeur_Cr)/2 ;
                tab_echantillonnee[i][j].Y = tableau[i][j].Y;
                valeur_Cb = 0;
                valeur_Cr = 0;
            }
        }
    }
    return tab_echantillonnee;

}


Triplet_YCbCr** ss_echantillonnage420(Triplet_YCbCr** tableau, uint32_t lignes, uint32_t col){
    Triplet_YCbCr** tab_echantillonnee = malloc(lignes * sizeof(Triplet_YCbCr*));
    for (uint32_t i = 0; i < lignes; i++)
    {
        tab_echantillonnee[i] = malloc(col * sizeof(Triplet_YCbCr));

        for (uint32_t k=0; k < col; k++)
        {
            if (!(i%2==0)){
                // separation des cas pour faire les moyennes des composantes

                if (i==0 && k == 0){
                    tab_echantillonnee[i][k].Cb = (tableau[i+1][k].Cb + tableau[i][k+1].Cb + tableau[i+1][k+1].Cb)/3 ;
                    tab_echantillonnee[i][k].Cr = (tableau[i+1][k].Cr + tableau[i][k+1].Cr + tableau[i+1][k+1].Cr)/3 ;
                }
                else if(i==0 && k ==col-1){
                    tab_echantillonnee[i][k].Cb = (tableau[i+1][k].Cb + tableau[i][k-1].Cb + tableau[i+1][k-1].Cb)/3 ;
                    tab_echantillonnee[i][k].Cr = (tableau[i+1][k].Cr + tableau[i][k-1].Cr + tableau[i+1][k-1].Cr)/3 ;
                }
                else if(i==lignes-1 && k ==col-1){
                    tab_echantillonnee[i][k].Cb = (tableau[i-1][k].Cb + tableau[i][k-1].Cb + tableau[i-1][k-1].Cb)/3 ;
                    tab_echantillonnee[i][k].Cr = (tableau[i-1][k].Cr + tableau[i][k-1].Cr + tableau[i-1][k-1].Cr)/3 ;
                }
                else if(i==lignes-1 && k ==0){
                    tab_echantillonnee[i][k].Cb = (tableau[i-1][k].Cb + tableau[i][k+1].Cb + tableau[i-1][k+1].Cb)/3 ;
                    tab_echantillonnee[i][k].Cr = (tableau[i-1][k].Cr + tableau[i][k+1].Cr + tableau[i-1][k+1].Cr)/3 ;
                }
                else if (i==0){
                    tab_echantillonnee[i][k].Cb = (tableau[i+1][k].Cb + tableau[i][k+1].Cb + tableau[i+1][k+1].Cb + tableau[i][k-1].Cb  + tableau[i+1][k-1].Cb)/5 ;
                    tab_echantillonnee[i][k].Cr = (tableau[i+1][k].Cr + tableau[i][k+1].Cr + tableau[i+1][k+1].Cr + tableau[i][k-1].Cr  + tableau[i+1][k-1].Cr)/5 ;
                }
                else if (k==0){
                    tab_echantillonnee[i][k].Cb = (tableau[i+1][k].Cb + tableau[i][k+1].Cb + tableau[i+1][k+1].Cb + tableau[i-1][k].Cb + tableau[i-1][k+1].Cb )/5 ;
                    tab_echantillonnee[i][k].Cr = (tableau[i+1][k].Cr + tableau[i][k+1].Cr + tableau[i+1][k+1].Cr + tableau[i-1][k].Cr + tableau[i-1][k+1].Cr )/5 ;
                }
                else if (k == col-1){
                    tab_echantillonnee[i][k].Cb = (tableau[i+1][k].Cb  + tableau[i-1][k].Cb + tableau[i-1][k-1].Cb + tableau[i][k-1].Cb  + tableau[i+1][k-1].Cb)/5 ;
                    tab_echantillonnee[i][k].Cr = (tableau[i+1][k].Cr  + tableau[i-1][k].Cr + tableau[i-1][k-1].Cr + tableau[i][k-1].Cr  + tableau[i+1][k-1].Cr)/5 ;
                }
                else if (i == lignes-1){
                    tab_echantillonnee[i][k].Cb = (tableau[i][k+1].Cb + tableau[i-1][k].Cb + tableau[i-1][k+1].Cb + tableau[i-1][k-1].Cb + tableau[i][k-1].Cb  )/5 ;
                    tab_echantillonnee[i][k].Cr = (tableau[i][k+1].Cr + tableau[i-1][k].Cr + tableau[i-1][k+1].Cr + tableau[i-1][k-1].Cr + tableau[i][k-1].Cr  )/5 ;
                }
                else{
                    tab_echantillonnee[i][k].Cb = (tableau[i+1][k].Cb + tableau[i][k+1].Cb + tableau[i+1][k+1].Cb + tableau[i-1][k].Cb + tableau[i-1][k+1].Cb + tableau[i-1][k-1].Cb + tableau[i][k-1].Cb  + tableau[i+1][k-1].Cb)/8 ;
                    tab_echantillonnee[i][k].Cr = (tableau[i+1][k].Cr + tableau[i][k+1].Cr + tableau[i+1][k+1].Cr + tableau[i-1][k].Cr + tableau[i-1][k+1].Cr + tableau[i-1][k-1].Cr + tableau[i][k-1].Cr  + tableau[i+1][k-1].Cr)/8 ;
                }
            }
            tab_echantillonnee[i][k].Y = tableau[i][k].Y;

        }
        for (uint32_t j = 0; j < col; j++)
        {
            if (i%2 == 0){
                tab_echantillonnee[i][j].Cb = 0;
                tab_echantillonnee[i][j].Cr = 0;
            }
            else{
                if (j%2 == 0){
                    tab_echantillonnee[i][j].Cb = 0;
                    tab_echantillonnee[i][j].Cr = 0;
                }
            }
        }
    }
    return tab_echantillonnee;

}



void free_tab_echantillonnee(Triplet_YCbCr** tab){
    free(tab);
}

uint8_t probleme_echantillonnage()
{
    printf("Probleme d'echantillonnage\n");
    printf("Error: Il faut le bon format : h1xv1,h2xv2,h3xv3 \n");
    printf("La valeur de chaque facteur h ou v doit être comprise entre 1 et 4 \n");
    printf("La somme des produits hi x vi doit etre <= 10 \n");
    printf("Les facteurs d'échantillonnage des chrominances doivent diviser parfaitement ceux de la luminance. \n");
    return 0;
}

bool verif_rectriction(uint8_t h1,uint8_t v1,uint8_t h2,uint8_t v2,uint8_t h3,uint8_t v3)
{
    if (h1 < 1 || h1 > 4 || v1 < 1 || v1 > 4 || h2 < 1 || h2 > 4 || v2 < 1 || v2 > 4 || h3 < 1 || h3 > 4 || v3 < 1 || v3 > 4)
    {
        return false;
    }
    if (h1 * v1 + h2 * v2 + h3 * v3 > 10)
    {
        return false;
    }
    if (h1 % h2 != 0 || h1 % h3 != 0 || v1 % v2 != 0 || v1 % v3 != 0)
    {
        return false;
    }
    return true;
}

uint8_t echantillonage(char* sample_factors) {
    char* pair = strtok(sample_factors, ",");
    uint8_t value[6];
    uint8_t competure = 0;

    while (pair != NULL) {
        char* h = strtok(pair, "x");
        if (h == NULL) {
            return probleme_echantillonnage();
        }
        value[competure] = atoi(h);
        competure++;

        char* v = strtok(NULL, "x");
        if (v == NULL) {
            return probleme_echantillonnage();
        }
        value[competure] = atoi(v);
        competure++;

        pair = strtok(NULL, ",");
    }
    free(pair);
    uint8_t h1 = value[0];
    uint8_t v1 = value[1];
    uint8_t h2 = value[2];
    uint8_t v2 = value[3];
    uint8_t h3 = value[4];
    uint8_t v3 = value[5];
    bool possible = verif_rectriction(h1, v1, h2, v2, h3, v3);
    if (!possible) {
        return probleme_echantillonnage();
    }
    printf("Good\n");
    
    return 1;
}

// int main() {
//     char sample_factors[] = "2x2,1x1,1x1";
//     echantillonage(sample_factors);
//     return 0;
// }
