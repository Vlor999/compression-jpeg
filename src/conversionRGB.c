#include <stdio.h>
#include <stdint.h>
#include "../include/conversionRGB.h"
#include "../include/recupereimage.h"
#include <stdlib.h>


Triplet_YCbCr conversionRGB(Triplet_RGB pixel){
    Triplet_YCbCr pixel_YCbCr;
    pixel_YCbCr.Y = 0.299* pixel.R + 0.587* pixel.G + 0.114* pixel.B;
    pixel_YCbCr.Cb = (-0.1687)* pixel.R - 0.3313* pixel.G + 0.5* pixel.B + 128;
    pixel_YCbCr.Cr = 0.5* pixel.R - 0.4187 * pixel.G - 0.0813*pixel.B + 128;
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

// int main(){
//     imagePGM* image = recupereimage("../images/invader.pgm");
//     Triplet_Y** new_image = conversionRGB_2_VCrCb(image);
//     for (int i = 0; i < image->ligne; i++)
//     {
//         for (int j = 0; j < image->col; j++)
//         {
//             printf("Y: %f, Cb: %f, Cr: %f\n", new_image[i][j].Y, new_image[i][j].Cb, new_image[i][j].Cr);
//         }
//     }
//     return 0;
// }

