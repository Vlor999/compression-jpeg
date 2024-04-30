#ifndef _CONVERSION_RGB_H
#define _CONVERSION_RGB_H
#include "recupereimage.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct Triplet_RGB{
    int8_t R;
    int8_t G;
    int8_t B;
}Triplet_RGB;

typedef struct Triplet_Y{
    float Y;
    float Cb;
    float Cr;
}Triplet_Y;


/**
 * @brief fais conversion de RGB vers YCbCr
 *
 * @param pixel triplet_RGB qui correspond à 1 seul pixel, il faut donc appliquer la fonction sur tous les pixels
 * @return pixel au format YCbCr ou les parametre du triplet (Y, Cb, Cr) sont des floats
 */


Triplet_Y conversionRGB(Triplet_RGB pixel);


/**
 * @brief fait la conversion de toute l image vers YCbCr
 *
 * @param img l'image en question
 * @return une matrice qui contient les YCbCr correspondants 
 */

Triplet_Y **conversiontotale(imagePGM *img);

#endif
