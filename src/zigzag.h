#ifndef _ZIGZAG_H
#define _ZIGZAG_H

#include <stdint.h>

/**
 * @brief Fonction qui permet de parcourir une matrice en zigzag
 * @param matrice la matrice à parcourir
 * @return un tableau 1D de taille 64
 * **/

int16_t* zigzag_matrice(int16_t** matrice);

/**
 * @brief Fonction qui permet de parcourir une matrice en zigzag mais sans boucle
 * @param matrice la matrice à parcourir
 * @return un tableau 1D de taille 64
 * **/

int16_t* zigzag_matrice1(int16_t** matrice);


#endif