#include <stdio.h>
#include <stdint.h>
#include "../include/conversionRGB.h"
#include "../include/recupereimage.h"
#include <stdlib.h>
#include <math.h>
#include "../include/recup_v2.h"

Triplet_YCbCr conversionRGB(Triplet_RGB pixel){
    Triplet_YCbCr pixel_YCbCr;
    float R = (float) pixel.R;
    float G = (float) pixel.G;
    float B = (float) pixel.B;
    pixel_YCbCr.Y = 0.299 * R + 0.587 * G + 0.114 * B;
    pixel_YCbCr.Cb = (-0.1687) * R - 0.3313 * G + 0.5 * B + 128;
    pixel_YCbCr.Cr = 0.5 * R - 0.4187 * G - 0.0813 * B + 128;
    return pixel_YCbCr;
}

Triplet_YCbCr** conversionRGB_2_VCrCb(imagePGM *image)
{
    Triplet_RGB pixel;
    Triplet_YCbCr pixel_YCbCr;

    int taille_ligne = image->ligne;
    int taille_col = image->col;

    Triplet_YCbCr **tab_YCbCr = malloc(taille_ligne * sizeof(Triplet_YCbCr *));
    
    for (int lig = 0; lig < taille_ligne; lig++)
    {
        tab_YCbCr[lig] = malloc(taille_col * sizeof(Triplet_YCbCr));
        for (int col = 0; col < taille_col; col++)
        {
            pixel.R = image->tab[lig][col];
            pixel.G = image->tab[lig][col];
            pixel.B = image->tab[lig][col];
            pixel_YCbCr = conversionRGB(pixel);
            tab_YCbCr[lig][col] = pixel_YCbCr;
        }
    }
    return tab_YCbCr;
}


Triplet_YCbCr** conversionRGB_2_YCrCb(imagePGM_RGB *image)
{
    Triplet_RGB pixel;
    Triplet_YCbCr pixel_YCbCr;

    int taille_ligne = image->ligne;
    int taille_col = image->col;

    Triplet_YCbCr **tab_YCbCr = malloc(taille_ligne * sizeof(Triplet_YCbCr *));
    
    for (int lig = 0; lig < taille_ligne; lig++)
    {
        tab_YCbCr[lig] = malloc(taille_col * sizeof(Triplet_YCbCr));
        for (int col = 0; col < taille_col; col++)
        {
            pixel = image->tab[lig][col];
            pixel_YCbCr = conversionRGB(pixel);
            pixel_YCbCr = pixel_YCbCr;
        }
    }
    return tab_YCbCr;
}

uint8_t approx_value(float value)
{
    if (value - floor(value) < 0.5)
    {
        return (uint8_t)value;
    }
    else{
        return (uint8_t)value + 1;
    }
}

uint8_t*** conversionRGB_2_YCrCb_MCU(MCU_RGB *mcu)
{
    Triplet_RGB pixel;
    Triplet_YCbCr pixel_YCbCr;
    uint8_t ***res = malloc(3 * sizeof(uint8_t**));    
    res[0] = malloc(MCU_TAILLE * sizeof(uint8_t*));
    res[1] = malloc(MCU_TAILLE * sizeof(uint8_t*));
    res[2] = malloc(MCU_TAILLE * sizeof(uint8_t*));
    
    for (uint8_t lig = 0; lig < MCU_TAILLE; lig++)
    {
        res[0][lig] = malloc(MCU_TAILLE * sizeof(uint8_t));
        res[1][lig] = malloc(MCU_TAILLE * sizeof(uint8_t));
        res[2][lig] = malloc(MCU_TAILLE * sizeof(uint8_t));
        for (uint8_t col = 0; col < MCU_TAILLE; col++)
        {
            pixel = mcu->tab[lig][col];
            pixel_YCbCr = conversionRGB(pixel); 
            res[0][lig][col] = approx_value(pixel_YCbCr.Y);
            res[1][lig][col] = approx_value(pixel_YCbCr.Cb);
            res[2][lig][col] = approx_value(pixel_YCbCr.Cr);
        }
    }
    return res;
}


