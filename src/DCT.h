#ifndef _DCT_H
#define _DCT_H
#include "MCU.h"
#include <stdint.h>

#include <stdint.h>

/*
    *  @brief calcule la DCT pour une valeur 
    *  @param un MCU,i,j les indices du bloc 
    *  @return la DCT 
*/

int16_t calcul_dct(Mcu *m,uint8_t i, uint8_t j);

/*
    *  @brief construit la matrice des DCT 
    *  @param le MCU voulu 
    *  @return la matrice des DCT 
*/

int16_t **dct(Mcu *m);

#endif