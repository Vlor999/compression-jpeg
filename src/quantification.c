#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../include/qtables.h"

int16_t* quotient(int16_t* vector1, uint8_t* vector2, int size) 
{
    /*
    Je fais ici le rapport des coefficients et l'inscrit dans le nouveau vecteur 
    Je ne sais pas si cela focntionne vraiment bien, mais je pense que oui
    */
    int16_t* result = malloc(size * sizeof(int));
    
    for (int i = 0; i < size; i++) {
        result[i] = (int16_t)((vector1[i] + vector2[i] / 2) / vector2[i]);
    }
    
    return result;
}

int16_t* quotient_qtable_Y(int16_t* vect, int size)
{
    uint8_t *vect2 = quantification_table_Y;
    return quotient(vect, vect2, size);
}

int16_t* quotient_qtable_CbCr(int16_t* vect, int size)
{
    uint8_t *vect2 = quantification_table_CbCr;
    return quotient(vect, vect2, size);
}

int main()
{
    /*
    ici je ne comprends pas car les valeurs ne correpsondent pas à ce qui est donné
    */
    int16_t vect[64] = {0x0183, 0x0086, 0xff2e, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
                    17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
                    31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44,
                    45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58,
                    59, 60, 61, 62, 63, 64};
    int16_t* result_Y = quotient_qtable_Y(vect, 64);
    int16_t* result_CbCr = quotient_qtable_CbCr(vect, 64);
    
    for (int i = 0; i < 64; i++) {
        printf("%x ", result_Y[i]);
    }
    printf("\n");
    
    for (int i = 0; i < 64; i++) {
        printf("%x ", result_CbCr[i]);
    }
    printf("\n");
    
    free(result_Y);
    free(result_CbCr);
    
    return 0;
}
