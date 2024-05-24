#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../include/qtables.h"
#include <math.h>

int16_t* quotient(int16_t* vector1, uint8_t* vector2) 
{
    /*
    Je fais ici le rapport des coefficients et l'inscrit dans le nouveau vecteur 
    Je ne sais pas si cela focntionne vraiment bien, mais je pense que oui
    */
    int16_t* result = malloc(64 * sizeof(int));
    
    for (uint8_t i = 0; i < 64; i++) 
    {
        result[i] = floor(vector1[i] / vector2[i]);
    }
    return result;
}

int16_t* quotient_qtable_Y(int16_t* vect)
{
    uint8_t *vect2 = quantification_table_Y;
    return quotient(vect, vect2);
}

int16_t* quotient_qtable_CbCr(int16_t* vect)
{
    uint8_t *vect2 = quantification_table_CbCr;
    return quotient(vect, vect2);
}
