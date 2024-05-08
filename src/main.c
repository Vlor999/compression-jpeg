#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/conversionRGB.h"
#include "../include/recupereimage.h"
#include "../include/conversionRGB.h"
#include "../include/zigzag.h"
#include "../include/quantification.h"
#include "../include/magnetude_dc.h"
#include "../include/MCU.h"
#include "../include/DCT.h"
#include "../include/jpeg_format.h"
#include "../include/htables.h"
#include <math.h>
#include "../include/qtables.h"
#include "../include/recup_v2.h"
#include "../include/option_main.h"

int main(int argc, char **argv)
{

    bool couleur = false; // pour mettre en couleur ou non 

    Arguments mes_arguments = utilisation_argument(argc, argv);
    char* filename = mes_arguments.output;
    char* input = mes_arguments.input;
    char* sample_factors = mes_arguments.sample_factors;
    if (!input)
    {
        return 1;
    }

    printf("input : %s\n", input);
    printf("output : %s\n", filename);
    printf("sample_factors : %s\n", sample_factors);

    imagePGM_RGB *img = LecturePPM(input); // nom du fichier a preciser   
    printf("Images initales : \n");
    for (uint32_t i= 0; i < img->ligne; i++){
        for (uint32_t j = 0; j < img->col; j ++){
            printf("%02x\t ", img->tab[i][j].R);   
        }
        printf("\n");
    }
    printf("\n\n"); 
       for (uint32_t i= 0; i < img->ligne; i++){
        for (uint32_t j = 0; j < img->col; j ++){
            printf("%02x\t ", img->tab[i][j].G);   
        }
        printf("\n");
    }
    printf("\n\n");
       for (uint32_t i= 0; i < img->ligne; i++){
        for (uint32_t j = 0; j < img->col; j ++){
            printf("%02x\t ", img->tab[i][j].B);   
        }
        printf("\n");
    }
    printf("\n");
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

    printf("%d %d\n", nb_ligne,nb_col);

    // uint32_t nb_ligne = img->ligne;
    // uint32_t nb_col = img->col;

    Triplet_YCbCr** new_image = conversionRGB_2_YCrCb(img); //violent le passage à l'entier ?
    uint8_t** image_Y = malloc(img->ligne * sizeof(uint8_t*));
    uint8_t** image_Cb = malloc(img->ligne * sizeof(uint8_t*));
    uint8_t** image_Cr = malloc(img->ligne * sizeof(uint8_t*));
    for (uint32_t i = 0; i < img->ligne; i++)
    {
        image_Y[i] = malloc(img->col * sizeof(uint8_t));
        image_Cb[i] = malloc(img->col * sizeof(uint8_t));
        image_Cr[i] = malloc(img->col * sizeof(uint8_t));
        for (uint32_t j = 0; j < img->col; j++)
        {   
            if (new_image[i][j].Y - floor(new_image[i][j].Y) < 0.5){
                image_Y[i][j] = (uint8_t) new_image[i][j].Y;
            }
            else{
                image_Y[i][j] = ((uint8_t) new_image[i][j].Y) + 1;
            }
            if (new_image[i][j].Cb - floor(new_image[i][j].Cb) < 0.5){
                image_Cb[i][j] = (uint8_t) new_image[i][j].Cb;
            }
            else{
                image_Cb[i][j] = ((uint8_t) new_image[i][j].Cb) + 1;
            }
            if (new_image[i][j].Cr - floor(new_image[i][j].Cr) < 0.5){
                image_Cr[i][j] = (uint8_t) new_image[i][j].Cr;
            }
            else{
                image_Cr[i][j] = ((uint8_t) new_image[i][j].Cr) + 1;
            }
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
    
    
    imagePGM *PGM_Y2 = nouveau_tableau(&PGM_Y);
    imagePGM *PGM_Cb2 = nouveau_tableau(&PGM_Cb);
    imagePGM *PGM_Cr2 = nouveau_tableau(&PGM_Cr);

    printf("%d %d\n",PGM_Y2->ligne,PGM_Y2->col);

    
    FILE* fptr = fopen(filename, "wb");
    printf("rgnrgnreungrug\n");
    ecrire_debut(fptr); 
    ecrire_commentaire_SOS_PC(fptr);
    ecrire_qtable(fptr, quantification_table_Y, quantification_table_CbCr,couleur);
    ecrire_SOF(fptr, img->ligne, img -> col,couleur); // faire en sorte qu'il change en fonction de l'image
    ecrire_htable(fptr,htables_symbols[0][0],htables_symbols[1][0],htables_symbols[0][1],htables_symbols[1][1],htables_nb_symb_per_lengths,couleur);
    ecrire_SOS_en_tete(fptr,couleur);
    int16_t prec_Y=0;
    int16_t prec_Cb=0;
    int16_t prec_Cr=0;
    ecritureSOS *ecr = malloc(sizeof(ecritureSOS));
    ecr -> nb = 0;
    uint8_t *RLE;
    uint8_t *resultat_final;
    ecr -> compteur = 7;
    uint32_t compteur;
    for (int i=0;i<PGM_Y2->ligne;i=i+8){
        for (int j=0;j<PGM_Y2->col;j=j+8){
            
            uint8_t **img_Y_MCU = decoupage(PGM_Y2,i,j);
            uint8_t **img_Cb_MCU = decoupage(PGM_Cb2,i,j);
            uint8_t **img_Cr_MCU = decoupage(PGM_Cr2,i,j);

            //Partie Y
            int16_t **img_Y_DCT = dct(img_Y_MCU);
            int16_t* img_Y_ZigZag = zigzag_matrice(img_Y_DCT);
            int16_t* img_Y_quantifie = quotient_qtable_Y(img_Y_ZigZag);
            RLE = codage_AC_RLE(img_Y_quantifie); 
            resultat_final = codage_total_AC_DC_Y(RLE, prec_Y, img_Y_quantifie);
            ecr = ecrire_SOS_contenu(fptr,resultat_final,ecr);
            //printf("TEST compteur %d nb %d \n\n\n", ecr -> compteur, ecr -> nb);
            prec_Y = img_Y_quantifie[0];


            if (couleur){ //on fait Cb et Cr 
                printf("enerve\n\n");

                //Partie Cb
                int16_t **img_Cb_DCT = dct(img_Cb_MCU);
                int16_t* img_Cb_ZigZag = zigzag_matrice(img_Cb_DCT);
                int16_t* img_Cb_quantifie = quotient_qtable_CbCr(img_Cb_ZigZag);
                RLE = codage_AC_RLE(img_Cb_quantifie); 
                resultat_final = codage_total_AC_DC_CbCr(RLE, prec_Cb, img_Cb_quantifie);
                ecr = ecrire_SOS_contenu(fptr,resultat_final,ecr);
                prec_Cb = img_Cb_quantifie[0];

                //Partie Cr
                int16_t **img_Cr_DCT = dct(img_Cr_MCU);
                int16_t* img_Cr_ZigZag = zigzag_matrice(img_Cr_DCT);
                int16_t* img_Cr_quantifie = quotient_qtable_CbCr(img_Cr_ZigZag);
                RLE = codage_AC_RLE(img_Cr_quantifie); 
                resultat_final = codage_total_AC_DC_CbCr(RLE, prec_Cr, img_Cr_quantifie);
                ecr = ecrire_SOS_contenu(fptr,resultat_final,ecr);
                prec_Cr = img_Cr_quantifie[0];
                printf("COMTPEUR %d\n",compteur);
                compteur++;
                printf("\n\nMCU Y\n\n");
                for (int i=0;i<8;i++){
                    for (int j=0;j<8;j++){
                        printf("%02x\t ",img_Y_MCU[i][j] &0xFFFF);
                    }
                    printf("\n");
                }
                printf("\n\nMCU Cb\n\n");
                for (int i=0;i<8;i++){
                    for (int j=0;j<8;j++){
                        printf("%02x\t ",img_Cb_MCU[i][j] &0xFFFF);
                    }
                    printf("\n");
                }
                printf("\n\nMCU Cr\n\n");
                for (int i=0;i<8;i++){
                    for (int j=0;j<8;j++){
                        printf("%02x\t ",img_Cr_MCU[i][j] &0xFFFF);
                    }
                    printf("\n");
                }
                printf("\n\nDCT Y\n\n");
                for (int i=0;i<8;i++){
                    for (int j=0;j<8;j++){
                        printf("%04x\t ",img_Y_DCT[i][j] &0xFFFF);
                    }
                    printf("\n");
                }
                printf("\n\nDCT Cb\n\n");
                for (int i=0;i<8;i++){
                    for (int j=0;j<8;j++){
                        printf("%04x\t ",img_Cb_DCT[i][j] &0xFFFF);
                    }
                    printf("\n");
                }
                printf("\n\nDCT Cr\n\n");
                for (int i=0;i<8;i++){
                    for (int j=0;j<8;j++){
                        printf("%04x\t ",img_Cr_DCT[i][j] &0xFFFF);
                    }
                    printf("\n");
                }

                printf("\n\n");
            }
        
        //prec_Cr = img_Cr_quantifie[0];


//         for (uint64_t i = 0;i<30000; i++)
//         { // résultat du flux de l encodage, a voir si c est bien ce qui est demandé 
//             if (resultat_final[i]==88){
//                 break;
//             }
//             GRAND_TABLEAU[indice+i] = resultat_final[i];
//             indice++;
//         }   
        }
    }
//     GRAND_TABLEAU[indice]=88;
//     indice++;
    if (ecr -> compteur != -1){
        fwrite(&(ecr -> nb), sizeof(uint8_t),1,fptr);
    }
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
