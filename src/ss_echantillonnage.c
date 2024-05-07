#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../include/conversionRGB.h"
#include "../include/recup_v2.h"


Triplet_YCbCr** ss_echantillonnage422(Triplet_YCbCr** tableau, uint32_t lignes, uint32_t col){
    Triplet_YCbCr** tab_echantillonnee = malloc(lignes * sizeof(Triplet_YCbCr*));
    float valeur_Cb;
    float valeur_Cr;
    for (int i = 0; i < lignes; i++)
    {
        tab_echantillonnee[i] = malloc(col * sizeof(Triplet_YCbCr));
        for (int j = 0; j < col; j++)
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
    for (int i = 0; i < lignes; i++)
    {
        tab_echantillonnee[i] = malloc(col * sizeof(Triplet_YCbCr));

        for (int k=0; k < col; k++)
        {
            if (!(i%2==0)){
                // separation des cas pour faire les moyennes des composantes

                if (i==0 & k == 0){
                    tab_echantillonnee[i][k].Cb = (tableau[i+1][k].Cb + tableau[i][k+1].Cb + tableau[i+1][k+1].Cb)/3 ;
                    tab_echantillonnee[i][k].Cr = (tableau[i+1][k].Cr + tableau[i][k+1].Cr + tableau[i+1][k+1].Cr)/3 ;
                }
                else if(i==0 & k ==col-1){
                    tab_echantillonnee[i][k].Cb = (tableau[i+1][k].Cb + tableau[i][k-1].Cb + tableau[i+1][k-1].Cb)/3 ;
                    tab_echantillonnee[i][k].Cr = (tableau[i+1][k].Cr + tableau[i][k-1].Cr + tableau[i+1][k-1].Cr)/3 ;
                }
                else if(i==lignes-1 & k ==col-1){
                    tab_echantillonnee[i][k].Cb = (tableau[i-1][k].Cb + tableau[i][k-1].Cb + tableau[i-1][k-1].Cb)/3 ;
                    tab_echantillonnee[i][k].Cr = (tableau[i-1][k].Cr + tableau[i][k-1].Cr + tableau[i-1][k-1].Cr)/3 ;
                }
                else if(i==lignes-1 & k ==0){
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
        for (int j = 0; j < col; j++)
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


// Triplet_YCbCr** decide_echantillonnage(Triplet_YCbCr** tableau, char* facteurs){
//     //oi
// }



int main(){
    char* facteur = "2x2,1x1,1x1";
    
}