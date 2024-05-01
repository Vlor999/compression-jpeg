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

uint16_t calcul_dct(Mcu *m,uint16_t i, uint16_t j);

/*
    *  @brief construit la matrice des DCT 
    *  @param le MCU voulu 
    *  @return la matrice des DCT 
*/

uint16_t **dct(Mcu *m);

#endif