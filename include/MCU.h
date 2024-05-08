#ifndef _MCU_H
#define _MCU_H
#include <stdlib.h>
#include <stdint.h>
#include "recupereimage.h"

struct MCU{
    uint8_t **tab; //tableau qui contient tous degrés de gris  
    uint32_t ligne; //savoir quelle ligne on est dans les MCUs (pas nécessaire mais facilite les calculs), on compte 8 par 8 
    uint32_t colonne; //savoir quelle colonne on est dans les MCUs (pas nécessaire mais facilite les calculs), on compte 8 par 8 
    struct MCU *suiv; //prochain Mcu
};

typedef struct MCU MCU;

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
MCU *decoupage(imagePGM *tab, uint32_t i, uint32_t j);

imagePGM *nouveau_tableau(imagePGM *image);

/*
    *  @brief libère la mémoire
    *  @param la tete de liste chainée
*/
void free_decoupage(MCU *m);


#endif
