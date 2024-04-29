#include "MCU.h"
#include <stdint.h>

/*
    *  @brief calcule la DCT pour une valeur 
    *  @param un MCU,i,j les indices du bloc 
    *  @return la DCT 
*/

double calcul_dct(Mcu *m,uint32_t i, uint32_t j);

/*
    *  @brief construit la matrice des DCT 
    *  @param le MCU voulu 
    *  @return la matrice des DCT 
*/

double **dct(Mcu *m);