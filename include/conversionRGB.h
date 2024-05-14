#ifndef _CONVERSION_RGB_H
#define _CONVERSION_RGB_H
#include "recupereimage.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#define MCU_TAILLE 8

typedef struct Triplet_RGB{
    uint8_t R;
    uint8_t G;
    uint8_t B;
}Triplet_RGB;

typedef struct Triplet_YCbCr{
    float Y;
    float Cb;
    float Cr;
}Triplet_YCbCr;

typedef struct imagePGM_RGB{
    uint16_t col;
    uint16_t ligne;
    uint32_t max;
    Triplet_RGB** tab;
}imagePGM_RGB;

typedef struct MCU_RGB
{
    Triplet_RGB tab[MCU_TAILLE][MCU_TAILLE];
}MCU_RGB;

typedef struct MCU_YCbCr
{
    Triplet_YCbCr tab[MCU_TAILLE][MCU_TAILLE];
}MCU_YCbCr;



/**
 * @brief fais conversion de RGB vers YCbCr
 *
 * @param pixel triplet_RGB qui correspond à 1 seul pixel, il faut donc appliquer la fonction sur tous les pixels
 * @return pixel au format YCbCr ou les parametre du triplet (Y, Cb, Cr) sont des floats
 */


Triplet_YCbCr conversionRGB(Triplet_RGB pixel);


/**
 * @brief fait la conversion de toute l image vers YCbCr
 *
 * @param img l'image en question
 * @return une matrice qui contient les YCbCr correspondants 
 */

Triplet_YCbCr** conversionRGB_2_VCrCb(imagePGM *image);

Triplet_YCbCr**conversionRGB_2_YCrCb(imagePGM_RGB *image); 

uint8_t ***conversionRGB_2_YCrCb_MCU(MCU_RGB *mcu);//dans le premier tableau tous les Y puis tous les Cb puis tous les Cr 

#endif
