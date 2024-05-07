#include "../include/conversionRGB.h"
#include "../include/recupereimage.h"
#include "../include/conversionRGB.h"
#include "../include/zigzag.h"
#include "../include/quantification.h"
#include "../include/magnetude_dc.h"
#include "../include/MCU.h"
#include "../include/DCT.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/jpeg_format.h"
#include "../include/htables.h"
#include "../include/qtables.h"
#include "../include/recup_v2.h"

int main(int argc, char **argv){
    if (argc != 3){
        perror("Ton daron en slibard\n");
    } 
    imagePGM_RGB *img = LecturePPM(argv[1]); // nom du fichier a preciser  
    printf("Images initales : \n");
    for (uint32_t i= 0; i < img->col; i++){
        for (uint32_t j = 0; j < img->ligne; j ++){
            printf("%04x\t ", img->tab[i][j].R);   
        }
        printf("\n");
    }
    uint16_t nb_ligne = 8*((uint16_t)img->ligne/8); 
    uint16_t nb_col = 8*((uint16_t)img->col/8);
    if (nb_ligne != img->ligne)
    {
        nb_ligne += 8;
    }
    if (nb_col != img->col)
    {
        nb_col += 8;
    }


    // uint32_t nb_ligne = img->ligne;
    // uint32_t nb_col = img->col;

    Triplet_YCbCr** new_image = conversionRGB_2_YCrCb(img);
    uint8_t** image_Y = malloc(img->col * sizeof(uint8_t*));
    uint8_t** image_Cb = malloc(img->col * sizeof(uint8_t*));
    uint8_t** image_Cr = malloc(img->col * sizeof(uint8_t*));
    for (uint32_t i = 0; i < img->col; i++)
    {
        image_Y[i] = malloc(img->ligne * sizeof(uint8_t));
        image_Cb[i] = malloc(img->ligne * sizeof(uint8_t));
        image_Cr[i] = malloc(img->ligne * sizeof(uint8_t));
        for (uint32_t j = 0; j < img->ligne; j++)
        {
            image_Y[i][j] = new_image[i][j].Y;
            image_Cb[i][j] = new_image[i][j].Cb;
            image_Cr[i][j] = new_image[i][j].Cr;
        }
    }

    printf("---------------------\n");
    // printf("Images Downsampling Y : \n");
    // for (uint32_t i = 0; i < img->col; i++)
    // {
    //     for (uint32_t j = 0; j < img->ligne; j++)
    //     {
    //         printf("%04x\t", image_Y[i][j]);
    //     }
    //     printf("\n");
    // }

    imagePGM PGM_Y = {img->col, img->ligne, img->max, image_Y};
    imagePGM PGM_Cb = {img->col, img->ligne, img->max, image_Cb};
    imagePGM PGM_Cr = {img->col, img->ligne, img->max, image_Cr};

    MCU* img_Y_MCU = decoupage(&PGM_Y);
    MCU* img_Cb_MCU = decoupage(&PGM_Cb);
    MCU* img_Cr_MCU = decoupage(&PGM_Cr);

    bool plus_que_un = (img_Y_MCU -> suiv != NULL);
    printf("IOFNEFIUNEF %d\n\n\n",plus_que_un);
    char* filename = argv[2];
    FILE* fptr = fopen(filename, "wb");
    ecrire_debut(fptr);
    ecrire_qtable(fptr, quantification_table_Y, quantification_table_CbCr);
    ecrire_SOF(fptr, nb_ligne, nb_col); // faire en sorte qu'il change en fonction de l'image
    ecrire_htable(fptr,htables_symbols[0][0],htables_symbols[1][0],htables_symbols[0][1],htables_symbols[1][1],htables_nb_symb_per_lengths);
    uint8_t *GRAND_TABLEAU = malloc(60000*sizeof(uint8_t));
    int16_t** img_Y_DCT = dct(img_Y_MCU);
    int16_t* img_Y_ZigZag = zigzag_matrice(img_Y_DCT);
    int16_t* img_Y_quantifie = quotient_qtable_Y(img_Y_ZigZag);
    uint8_t *RLE = codage_AC_RLE(img_Y_quantifie); 
    uint8_t *resultat_final = codage_total_AC_DC_Y(RLE, NULL, img_Y_quantifie, false);
    ecrire_SOS_en_tete(fptr);
    ecritureSOS *ecr = malloc(sizeof(ecritureSOS));
    ecr -> nb = 0;
    ecr -> compteur = 7;
    ecr = ecrire_SOS_contenu(fptr,resultat_final,ecr);
    // printf("y u bubugbrg\n"); 
    // if (plus_que_un){
    //     img_Y_MCU = img_Y_MCU -> suiv;
    // }
    MCU *img_Y_prec;
    while (img_Y_MCU->suiv != NULL)
    {
        printf("uiuuirugrgiurgrugri\n\n");
        int16_t** img_Y_DCT = dct(img_Y_MCU->suiv);
        int16_t* img_Y_ZigZag = zigzag_matrice(img_Y_DCT);
        int16_t* img_Y_quantifie = quotient_qtable_Y(img_Y_ZigZag);
        int16_t* img_Y_quantifie_prec = quotient_qtable_Y(zigzag_matrice(dct(img_Y_MCU)));
        uint8_t *RLE = codage_AC_RLE(img_Y_quantifie); 
        uint8_t *resultat_final = codage_total_AC_DC_Y(RLE, img_Y_quantifie_prec, img_Y_quantifie, true);
        ecr = ecrire_SOS_contenu(fptr,resultat_final,ecr);
        printf("TEST compteur %d nb %d \n\n\n", ecr -> compteur, ecr -> nb);
//         for (uint64_t i = 0;i<30000; i++)
//         { // résultat du flux de l encodage, a voir si c est bien ce qui est demandé 
//             if (resultat_final[i]==88){
//                 break;
//             }
//             GRAND_TABLEAU[indice+i] = resultat_final[i];
//             indice++;
//         }   
        img_Y_prec = img_Y_MCU;
        img_Y_MCU = img_Y_MCU->suiv;
    }
    
    // if (plus_que_un){
    //     printf("jniunrignr\n\n\n");
    //     img_Y_DCT = dct(img_Y_MCU);
    //     img_Y_ZigZag = zigzag_matrice(img_Y_DCT);
    //     img_Y_quantifie = quotient_qtable_Y(img_Y_ZigZag);
    //     RLE = codage_AC_RLE(img_Y_quantifie); 
    //     int16_t *img_Y_quantifie_prec = quotient_qtable_Y(zigzag_matrice(dct(img_Y_prec)));
    //     resultat_final = codage_total_AC_DC_Y(RLE, img_Y_quantifie_prec, img_Y_quantifie, true);
    //     ecr = ecrire_SOS_contenu(fptr,resultat_final,ecr);
    // }
//     GRAND_TABLEAU[indice]=88;
//     indice++;
    ecrire_fin(fptr);
    fclose(fptr);
    printf("fini\n");

    // int16_t** img_Y_DCT = dct(img_Y_MCU);
    // int16_t** img_Cb_DCT = dct(img_Cb_MCU);
    // int16_t** img_Cr_DCT = dct(img_Cr_MCU);

    // printf("---------------------\n");
    // printf("Images DCT Y : \n");
    // for(uint32_t i = 0; i < 8; i++)
    // {
    //     for(uint32_t j = 0; j < 8 ; j++)
    //     {
    //         printf("%04x\t", img_Y_DCT[i][j] & 0xFFFF);
    //     }
    //     printf("\n");
    // }

    // int16_t* img_Y_ZigZag = zigzag_matrice(img_Y_DCT);
    // int16_t* img_Cb_ZigZag = zigzag_matrice(img_Cb_DCT);
    // int16_t* img_Cr_ZigZag = zigzag_matrice(img_Cr_DCT);

    // printf("---------------------\n");
    // printf("Images ZigZag Y : \n");
    // for (uint8_t i = 0; i < 8; i++)
    // {
    //     for (uint8_t j = 0; j < 8 ; j++)
    //     {
    //         printf("%04x\t", img_Y_ZigZag[i * 8 + j] & 0xFFFF);
    //     }
    //     printf("\n");
    // }

    // int16_t* img_Y_quantifie = quotient_qtable_Y(img_Y_ZigZag, 64);
    // int16_t* img_Cb_quantifie = quotient_qtable_CbCr(img_Cb_ZigZag, 64);
    // int16_t* img_Cr_quantifie = quotient_qtable_CbCr(img_Cr_ZigZag, 64);
    // printf("---------------------\n");
    // printf("Images Quantifie Y : \n");
    // for (uint32_t i = 0; i < 8 ; i++)
    // {
    //     for (uint32_t j = 0; j < 8; j++)
    //     {
    //         printf("%04x\t", img_Y_quantifie[i * 8 + j] & 0xFFFF);
    //     }
    //     printf("\n");
    // }
    // printf("---------------------\n");
    // printf("Coefficient DC \n");
    // uint8_t magnetude_Y = trouver_magnetude(img_Y_quantifie[0]);
    // uint8_t *DC_Y = codage_indice_magn(img_Y_quantifie[0]);
    // printf("value : %d, magnitude : %d", img_Y_quantifie[0],magnetude_Y );
    // uint16_t DC_Y_value = 0;
    // for (int i = 0; i < magnetude_Y; i++)
    // {
    //     DC_Y_value = DC_Y_value << 1 | DC_Y[i];
    // }
    // printf(", index : %d\n", DC_Y_value);
    
    // printf("\nfinal :");
    // uint8_t *code_Y_final = codage_total_DC_Y(img_Y_quantifie[0]);
    // for (uint8_t i=1;i<=code_Y_final[0];i++){
    //     printf("%d ", code_Y_final[i]);
    // }
    // //TEST AC
    // printf("\n");
    // printf("---------------------\n");
    // printf("Coefficients AC \n");
    // uint8_t *RLE = codage_AC_RLE(img_Y_quantifie); 
    // uint8_t *resultat_final = codage_total_AC_Y(RLE,img_Y_quantifie);
    // for (uint64_t i = 0;i<30000; i++){ // résultat du flux de l encodage, a voir si c est bien ce qui est demandé 
    //     if (resultat_final[i]==88){
    //         break;
    //     }
    //     printf("%d ", resultat_final[i]);
    // }
    // char* filename = argv[2];
    // FILE* fptr = fopen(filename, "wb");
    // ecrire_debut(fptr);
    // ecrire_qtable(fptr, quantification_table_Y, quantification_table_CbCr);
    // ecrire_SOF(fptr,8,8);
    // ecrire_htable(fptr,htables_symbols[0][0],htables_symbols[1][0],htables_symbols[0][1],htables_symbols[1][1],htables_nb_symb_per_lengths);
    // ecrire_SOS(fptr,resultat_final,1);
    // ecrire_fin(fptr);
    // fclose(fptr);
    // return 0;
    
    // for (uint8_t i=1;i<64;i++){
    //     if (img_Y_quantifie[i] != 0){
    //         magnetude_Y = trouver_magnetude(img_Y_quantifie[i]);
    //         printf("value : %d, magnitude : %d,", img_Y_quantifie[i],magnetude_Y );
    //         DC_Y = codage_indice_magn(img_Y_quantifie[i]);
    //         printf("index ");   
    //         for (int i = 0; i < magnetude_Y; i++)
    //         {
    //             printf(" %d",DC_Y[i]);
    //         }
    //         printf("\nfinal : ");
    //         code_Y_final = codage_total_AC_Y(img_Y_quantifie[i]);
    //         for (uint8_t i=1;i<=code_Y_final[0];i++){
    //             printf("%d ", code_Y_final[i]);
    //         }
    //         printf("\n");
    //     }
    // }
    // return 0;


}
