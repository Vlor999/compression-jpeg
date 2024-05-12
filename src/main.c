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
    Arguments mes_arguments = utilisation_argument(argc, argv);
    char* filename = mes_arguments.output;
    char* input = mes_arguments.input;
    char* sample_factors = mes_arguments.sample_factors;
    bool couleur = mes_arguments.couleur;
    bool verbose = mes_arguments.verbose;
    
    if (!input)
    {
        return 1;
    }

    printf("input : %s\n", input);
    printf("output : %s\n", filename);
    printf("sample_factors : %s\n", sample_factors);
    printf("couleur : %d\n", couleur);
    printf("verbose : %d\n", verbose);

    imagePGM_RGB *img = LecturePPM(input); // nom du fichier a preciser   

    Triplet_YCbCr** new_image = conversionRGB_2_YCrCb(img); 
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

    imagePGM PGM_Y = {img->col, img->ligne, img->max, image_Y};
    imagePGM PGM_Cb = {img->col, img->ligne, img->max, image_Cb};
    imagePGM PGM_Cr = {img->col, img->ligne, img->max, image_Cr};
    
    
    imagePGM *PGM_Y2 = nouveau_tableau(&PGM_Y);
    imagePGM *PGM_Cb2 = nouveau_tableau(&PGM_Cb);
    imagePGM *PGM_Cr2 = nouveau_tableau(&PGM_Cr);

    

    
    FILE* fptr = fopen(filename, "wb");
    ecrire_debut(fptr); 
    ecrire_commentaire_SOS_PC(fptr);
    ecrire_qtable(fptr, quantification_table_Y, quantification_table_CbCr, couleur);
    ecrire_SOF(fptr, img->ligne, img -> col,couleur); // faire en sorte qu'il change en fonction de l'image
    ecrire_htable(fptr, htables_nb_symb_per_lengths, couleur);
    ecrire_SOS_en_tete(fptr,couleur);
    int16_t prec_Y=0;
    int16_t prec_Cb=0;
    int16_t prec_Cr=0;
    ecritureSOS *ecr = malloc(sizeof(ecritureSOS));
    ecr -> nb = 0;
    uint8_t *RLE;
    uint8_t *resultat_final;
    ecr -> compteur = 7;
    uint8_t **img_MCU;
    int16_t* img_ZigZag;
    int16_t* img_quantifie;
    int16_t **img_DCT;
    for (int i=0;i<PGM_Y2->ligne;i=i+8){
        for (int j=0;j<PGM_Y2->col;j=j+8){
            
            img_MCU = decoupage(PGM_Y2,i,j);
            
            //Partie Y
            img_DCT = dct(img_MCU);
            img_ZigZag = zigzag_matrice1(img_DCT);
            img_quantifie = quotient_qtable_Y(img_ZigZag);
            RLE = codage_AC_RLE(img_quantifie); 
            resultat_final = codage_total_AC_DC_Y(RLE, prec_Y, img_quantifie, verbose);
            ecr = ecrire_SOS_contenu(fptr,resultat_final,ecr);
            prec_Y = img_quantifie[0]; //on sauvegarde en mémoire pour la magnétude

            if (couleur)
            { //on fait Cb et Cr 
                img_MCU = decoupage(PGM_Cb2,i,j);
                //Partie Cb
                img_DCT = dct(img_MCU);
                img_ZigZag = zigzag_matrice1(img_DCT);
                img_quantifie = quotient_qtable_CbCr(img_ZigZag);
                RLE = codage_AC_RLE(img_quantifie); 
                resultat_final = codage_total_AC_DC_CbCr(RLE, prec_Cb, img_quantifie, verbose);
                ecr = ecrire_SOS_contenu(fptr,resultat_final,ecr);
                prec_Cb = img_quantifie[0];

                //Partie Cr
                img_MCU = decoupage(PGM_Cr2,i,j);
                img_DCT = dct(img_MCU);
                img_ZigZag = zigzag_matrice1(img_DCT);
                img_quantifie = quotient_qtable_CbCr(img_ZigZag);
                RLE = codage_AC_RLE(img_quantifie); 
                resultat_final = codage_total_AC_DC_CbCr(RLE, prec_Cr, img_quantifie, verbose);
                ecr = ecrire_SOS_contenu(fptr,resultat_final,ecr);
                prec_Cr = img_quantifie[0];
            } 
        }
    }

    //fwrite(&(ecr -> nb), sizeof(uint8_t),1,fptr);

    ecrire_fin(fptr);
    fclose(fptr);
    printf("fini\n");

}