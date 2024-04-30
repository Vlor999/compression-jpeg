#include <stdlib.h>
#include <stdint.h>
#include "recupereimage.h"

struct Mcu{
    uint8_t **tab; //tableau qui contient tous degrés de gris  
    uint32_t ligne; //savoir quelle ligne on est dans les MCUs (pas nécessaire mais facilite les calculs)
    uint32_t colonne; //savoir quelle colonne on est dans les MCUs (pas nécessaire mais facilite les calculs)
    struct Mcu *suiv; //prochain Mcu
};

typedef struct Mcu Mcu;

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
Mcu *decoupage(imagePGM *tab);


/*
    *  @brief libère la mémoire
    *  @param la tete de liste chainée
*/
void free_decouapge(Mcu *m);
