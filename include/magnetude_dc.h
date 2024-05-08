#ifndef _MAGNETUDE_DC_H
#define _MAGNETUDE_DC_H
#include <stdint.h>
#include <stdbool.h>

/**
* @brief trouve la magnétude associée à n
* @param n l entier choisi 
* @return la magnétude, une erreur si n est trop grand
*
**/



uint8_t trouver_magnetude(int16_t n);


/**
* @brief trouve l'indice dans la classe de magnétude associée à n
* @param n l entier choisi 
* @return l'indice dans la classe magnétude, une erreur si n est trop grand
*
**/

// uint16_t indice_magnetude(int16_t n);


/**
 * @brief écrit les bits de poids fort pour l'octet AC
 * @param RLE le tableau RLE
 * @return un tableau 1D plus court sous forme 1222130 ou 30 veut dire 3 zero d'affilé
 * **/

uint8_t *bits_poids_forts(uint8_t *RLE);

/**
 * @brief recupère le tableau après zig zag et applique codage RLE sur 0 uniquement
 * @param tab le tableau donnée après zigzag !! l'indice 0 correspond à la taille du tableau
 * @return un tableau 1D plus court sous forme 1222130 ou 30 veut dire 3 zero d'affilé
 * **/

uint8_t* codage_AC_RLE(int16_t* tab);

/*
* @brief trouve le codage dc associé
* @entree n l entier choisi 
* @sortie le code dc 
*/


uint8_t *codage_indice_magn(int16_t n);


extern uint8_t code_DC_Y[12][10];

extern uint8_t code_DC_CbCr[12][11];

/**
 * @brief relie les deux codages pour n'en faire qu'un
 * @param n l'entier, code_associe le code de Huffman associe 
 * @return un tableau qui contient l'entete puis l indice de n 
 * **/

//ATTENTION PREMIERE VALEUR CONTIENT LA TAILLE
uint8_t *codage_total_DC_Y(int16_t n);

uint8_t *codage_total_DC_CbCr(int16_t n);

uint8_t *codage_total_AC_DC_CbCr(uint8_t *RLE, int16_t *flux, int16_t *flux2, bool changement_DC);


/**
 * @brief donne le flux de bits attendus en sortie 
 * @param RLE les valeurs RLE pour les codages, flux pour les blocs 8x8 à analyser, le flux précendent si on est sur la meme ligne, flux2 le flux actuel et 
 * le changement si on reste sur la meme ligne
 * @return le tableau avec tout le flux correspondant
 * **/
uint8_t *codage_total_AC_DC_Y(uint8_t *RLE, int16_t prec, int16_t *flux2, bool changement_DC);

#endif