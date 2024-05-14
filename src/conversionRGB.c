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
    pixel_YCbCr.Y = 0.299* R+ 0.587* G + 0.114* B;
    pixel_YCbCr.Cb = (-0.1687)* R - 0.3313* G + 0.5* B + 128;
    pixel_YCbCr.Cr = 0.5* R - 0.4187 * G - 0.0813*B + 128;
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

uint8_t ***conversionRGB_2_YCrCb_MCU(MCU_RGB *mcu)
{
    Triplet_RGB pixel;
    Triplet_YCbCr pixel_YCbCr;
    uint8_t ***res = malloc(3*sizeof(uint8_t**));    
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
            if (pixel_YCbCr.Y - floor(pixel_YCbCr.Y) < 0.5)
            {
                res[0][lig][col] = (uint8_t)pixel_YCbCr.Y;
            }
            else
            {
                res[0][lig][col] = ((uint8_t)pixel_YCbCr.Y) + 1;
            }
            if (pixel_YCbCr.Cb - floor(pixel_YCbCr.Cb) < 0.5)
            {
                res[1][lig][col] = (uint8_t)pixel_YCbCr.Cb;
            }
            else
            {
                res[1][lig][col] = ((uint8_t)pixel_YCbCr.Cb) + 1;
            }
            if (pixel_YCbCr.Cr - floor(pixel_YCbCr.Cr) < 0.5)
            {
                res[2][lig][col] = (uint8_t)pixel_YCbCr.Cr;
            }
            else
            {
                res[2][lig][col] = ((uint8_t)pixel_YCbCr.Cr) + 1;
            }
        }
    }
    return res;
}


// int main()
// {
//     for (uint16_t i = 0; i <= 255; i++)
//     {
//         for(uint16_t j = 0; j <= 255; j++)
//         {
//             for(uint16_t k = 0; k <= 255; k++)
//             {
//                 Triplet_RGB pixel;
//                 pixel.R = i;
//                 pixel.G = j;
//                 pixel.B = k;
//                 Triplet_YCbCr pixel_YCbCr = conversionRGB(pixel);
//                 printf("%02x%02x%02x, %f, %f, %f\n", pixel.R, pixel.G, pixel.B, pixel_YCbCr.Y, pixel_YCbCr.Cb, pixel_YCbCr.Cr);
//             }
//         }
        
//     }
// }

