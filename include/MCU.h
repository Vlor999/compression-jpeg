#ifndef _MCU_H
#define _MCU_H
#include <stdlib.h>
#include <stdint.h>
#include "recupereimage.h"

/*
    *  @brief trouve la partie entiere superieur pour le découpage 
    *  @param la longueur/largeur
    *  @return 8*PES(l/8)
*/
uint32_t entier_superieur(uint32_t l);

/*
    *  @brief Decoupe la matrice des pixels en blocs de 8x8x
    *  @param la matrice des pixels
    *  @return les MCUs sous forme de liste chainee, la valeur renvoyée étant la tete
*/
uint8_t **decoupage(imagePGM *tab, uint32_t i, uint32_t j);

imagePGM *nouveau_tableau(imagePGM *image);

#endif
