#include "conversionRGB.h"
#include "recupereimage.h"
#include "conversionRGB.h"
#include "MCU.h"
#include "MCU.h"
#include "DCT.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int main(){
    imagePGM *img = recupereimage("../images/invader.pgm"); // cest bon 
    printf("Images initales : \n");
    for (int i= 0; i < img->col; i++){
        for (int j = 0; j < img->ligne; j ++){
            printf("%x\t ", img->tab[i][j]);   
        }
        printf("\n");
    }

    Triplet_Y** new_image = conversionRGB_2_VCrCb(img);
    uint8_t** image_Y = malloc(img->col * sizeof(uint8_t*));
    uint8_t** image_Cb = malloc(img->col * sizeof(uint8_t*));
    uint8_t** image_Cr = malloc(img->col * sizeof(uint8_t*));
    for (int i = 0; i < img->col; i++)
    {
        image_Y[i] = malloc(img->ligne * sizeof(uint8_t));
        image_Cb[i] = malloc(img->ligne * sizeof(uint8_t));
        image_Cr[i] = malloc(img->ligne * sizeof(uint8_t));
        for (int j = 0; j < img->ligne; j++)
        {
            image_Y[i][j] = new_image[i][j].Y;
            image_Cb[i][j] = new_image[i][j].Cb;
            image_Cr[i][j] = new_image[i][j].Cr;
        }
    }

    printf("---------------------\n");
    printf("Images Downsampling Y : \n");
    for (int i = 0; i < img->col; i++)
    {
        for (int j = 0; j < img->ligne; j++)
        {
            printf("%x\t", image_Y[i][j]);
        }
        printf("\n");
    }

    imagePGM PGM_Y = {img->col, img->ligne, img->max, image_Y};
    imagePGM PGM_Cb = {img->col, img->ligne, img->max, image_Cb};
    imagePGM PGM_Cr = {img->col, img->ligne, img->max, image_Cr};

    Mcu* img_Y_MCU = decoupage(&PGM_Y);
    Mcu* img_Cb_MCU = decoupage(&PGM_Cb);
    Mcu* img_Cr_MCU = decoupage(&PGM_Cr);


    return 0;

    

}
