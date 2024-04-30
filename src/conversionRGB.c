#include <stdio.h>
#include <stdint.h>
#include "conversionRGB.h"
#include "recupereimage.h"
#include <stdlib.h>


Triplet_Y conversionRGB(Triplet_RGB pixel){
    Triplet_Y pixel_YCbCr;
    pixel_YCbCr.Y = 0.299* pixel.R + 0.587* pixel.G + 0.114* pixel.B;
    pixel_YCbCr.Cb = (-0.1687)* pixel.R - 0.3313* pixel.G + 0.5* pixel.B + 128;
    pixel_YCbCr.Cr = 0.5* pixel.R - 0.4187 * pixel.G - 0.0813*pixel.B + 128;
    return pixel_YCbCr;
}

Triplet_Y **conversiontotale(imagePGM *img){
    Triplet_RGB val;
    Triplet_Y val_Y;
    Triplet_Y** tab = malloc((img -> col)*sizeof(Triplet_Y*));
    printf("nirugrigre\n");
    for (int i= 0; i < img -> col; i++){
        tab[i] = malloc((img -> ligne)*sizeof(Triplet_Y));
        for (int j = 0; j < img -> ligne; j ++){
            val.R = img->tab[i][j];
            val.G = img->tab[i][j];
            val.B = img->tab[i][j];
            val_Y = conversionRGB(val);
            tab[i][j] = val_Y;
        }
    }
    for (int i= 0; i < img->ligne; i++){
        for (int j = 0; j < img->col; j ++){
            printf("%f",tab[i][j].Y);
            printf("%f",tab[i][j].Y);
            printf("%f",tab[i][j].Y);
            
        }
        printf("\n");
    }
    return tab;
}



