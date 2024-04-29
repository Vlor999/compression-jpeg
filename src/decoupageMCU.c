#include <stdio.h>
#include <stdlib.h>
#include "conversionRGB.h"
#include "MCU.h"
#include <stdbool.h>


uint32_t entier_superieur(uint32_t l){
    uint32_t tmp;
    if (l%8==0){
        return l;
    }
    else{
        return l + 8;
    }
}


Mcu *decoupage(imagePGM *img){ //A FINIR QUAND Y A PLUSIEURS MCU
    //POUR LE GRIS UNIQUEMENT APRES FAUT ALLER NIQUER SA MERE 
    uint32_t **tab = img -> tab;
    uint32_t hauteur = entier_superieur(img -> ligne);
    uint32_t largeur = entier_superieur(img -> col);
    Mcu *tete;
    Mcu *actuel;
    Mcu *tmp;
    bool debut = true;
    for (uint32_t indice_hauteur = 0; indice_hauteur < tab[0][1]; indice_hauteur = indice_hauteur + 8){
        for (uint32_t indice_largeur = 0; indice_largeur < tab[0][1]; indice_largeur = indice_largeur + 8){
            tmp = (Mcu*)malloc(sizeof(Mcu));
            tmp -> colonne = indice_largeur:
            tmp -> ligne = indice_hauteur;
            for (uint8_t i=0;i<8;i++){ //on remplit le CMU des pixels
                for (uint8_t j=0;j<8;j++){
                    (tmp -> tab)[i][j] = tab[indice_hauteur + i][indice_largeur + j];
                }
            }
            if (debut){ //on marque la tete
                tete = tmp;
                debut = false;
            }
            else{
                
            }
        }
    }
}

int main(){

    return 0;
}