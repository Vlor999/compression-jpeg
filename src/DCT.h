#include "MCU.h"
#include <stdint.h>

/*
    *  @brief calcule la DCT pour une valeur 
    *  @param un MCU,i,j les indices du bloc 
    *  @return la DCT 
*/

double calcul_dct(Mcu *m,uint32_t i, uint32_t j);