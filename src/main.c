#include "conversionRGB.h"
#include "recupereimage.h"
#include "conversionRGB.h"
#include "zigzag.h"
#include "quantification.h"
#include "magnetude_dc.h"
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
            printf("%04x\t ", img->tab[i][j]);   
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
            printf("%04x\t", image_Y[i][j]);
        }
        printf("\n");
    }

    imagePGM PGM_Y = {img->col, img->ligne, img->max, image_Y};
    imagePGM PGM_Cb = {img->col, img->ligne, img->max, image_Cb};
    imagePGM PGM_Cr = {img->col, img->ligne, img->max, image_Cr};

    Mcu* img_Y_MCU = decoupage(&PGM_Y);
    Mcu* img_Cb_MCU = decoupage(&PGM_Cb);
    Mcu* img_Cr_MCU = decoupage(&PGM_Cr);

    int16_t** img_Y_DCT = dct(img_Y_MCU);
    int16_t** img_Cb_DCT = dct(img_Cb_MCU);
    int16_t** img_Cr_DCT = dct(img_Cr_MCU);

    printf("---------------------\n");
    printf("Images DCT Y : \n");
    for(uint8_t i = 0; i < img_Y_MCU->colonne; i++)
    {
        for(uint8_t j = 0; j < img_Y_MCU->ligne; j++)
        {
            printf("%04x\t", img_Y_DCT[i][j] & 0xFFFF);
        }
        printf("\n");
    }

    int16_t* img_Y_ZigZag = zigzag_matrice(img_Y_DCT);
    int16_t* img_Cb_ZigZag = zigzag_matrice(img_Cb_DCT);
    int16_t* img_Cr_ZigZag = zigzag_matrice(img_Cr_DCT);

    printf("---------------------\n");
    printf("Images ZigZag Y : \n");
    for (uint8_t i = 0; i < img_Y_MCU->colonne; i++)
    {
        for (uint8_t j = 0; j < img_Y_MCU->ligne; j++)
        {
            printf("%04x\t", img_Y_ZigZag[i * img_Y_MCU->ligne + j] & 0xFFFF);
        }
        printf("\n");
    }

    int16_t* img_Y_quantifie = quotient_qtable_Y(img_Y_ZigZag, img_Y_MCU->colonne * img_Y_MCU->ligne);
    int16_t* img_Cb_quantifie = quotient_qtable_CbCr(img_Cb_ZigZag, img_Cb_MCU->colonne * img_Cb_MCU->ligne);
    int16_t* img_Cr_quantifie = quotient_qtable_CbCr(img_Cr_ZigZag, img_Cr_MCU->colonne * img_Cr_MCU->ligne);
    printf("---------------------\n");
    printf("Images Quantifie Y : \n");
    for (uint32_t i = 0; i < img_Y_MCU->colonne; i++)
    {
        for (uint32_t j = 0; j < img_Y_MCU->ligne; j++)
        {
            printf("%04x\t", img_Y_quantifie[i * img_Y_MCU->ligne + j] & 0xFFFF);
        }
        printf("\n");
    }
    printf("---------------------\n");
    printf("Coefficient DC \n");
    uint8_t magnetude_Y = trouver_magnetude(img_Y_quantifie[0]);
    uint8_t *DC_Y = codage_indice_magn(img_Y_quantifie[0]);
    printf("value : %d, magnitude : %d", img_Y_quantifie[0],magnetude_Y );
    // uint16_t DC_Y_value = 0;
    // for (int i = 0; i < magnetude_Y; i++)
    // {
    //     DC_Y_value = DC_Y_value << 1 | DC_Y[i];
    // }
    //printf(", index : %d\n", DC_Y_value);
    printf("\nfinal ");
    uint8_t *code_Y_final = codage_total_DC_Y(img_Y_quantifie[0]);
    for (int i=1;i<=code_Y_final[0];i++){
        printf("%d ", code_Y_final[i]);
    }
    printf("\n");
    return 0;

}
