#ifndef _QUANTIFICATION_H
#define _QUANTIFICATION_H

#include <stdint.h>

/**
* @brief Fonction qui fait le quotient terme à terme de deux vecteurs ligne
* @param le vecteur 1 est le vecteur "numérateur" et le vecteur 2 le veceteur "dénominateur" puis on à la taille des vecteurs
* @return vecteur 1 dimension du quotient effectué
**/

int16_t* quotient(uint16_t* vector1, uint8_t* vector2);

/**
 * @brief Utilise la focntion précédente pour utiliser la qtable sur Y**/
int16_t* quotient_qtable_Y(int16_t* vect);

/**
 * @brief Utilise la focntion précédente pour utiliser la qtable sur Cb ou Cr**/
int16_t* quotient_qtable_CbCr(int16_t* vect);

#endif