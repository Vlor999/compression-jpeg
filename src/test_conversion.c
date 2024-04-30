#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "recupereimage.h"
#include "conversionRGB.h"

int main(){
    imagePGM* image = recupereimage("our_images/alea_image0.pgm");
    Triplet_Y** tab;
    for (int i= 0; i < image->ligne; i++){
        for (int j = 0; j < image->col; j ++){
            Triplet_RGB val;
            val.R = image->tab[i][j];
            val.G = image->tab[i][j];
            val.B = image->tab[i][j];
            Triplet_Y val_Y = conversionRGB(val);
            tab[i][j] = val_Y;
        }
    }
    for (int i= 0; i < image->ligne; i++){
        for (int j = 0; j < image->col; j ++){
            printf("%f",tab[i][j].Y);
            printf("%f",tab[i][j].Y);
            printf("%f",tab[i][j].Y);
            printf("\n");
        }
    }
    return 0;
}