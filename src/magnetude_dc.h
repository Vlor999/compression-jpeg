#include <stdint.h>

/**
* @brief trouve la magnétude associée à n
* @param n l entier choisi 
* @return la magnétude, une erreur si n est trop grand
*
**/



uint8_t trouver_magnetude(int32_t n);


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


uint8_t *codage_dc_tete(int32_t n);