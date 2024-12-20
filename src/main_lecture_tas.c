#include <math.h>
#include <time.h> 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/DCT.h"
#include "../include/MCU.h"
#include "../include/zigzag.h"
#include "../include/htables.h"
#include "../include/recup_v2.h"
#include "../include/progression.h"
#include "../include/option_main.h"
#include "../include/jpeg_format.h"
#include "../include/magnetude_dc.h"
#include "../include/conversionRGB.h"
#include "../include/recupereimage.h"
#include "../include/conversionRGB.h"
#include "../include/quantification.h"
#include "../include/ss_echantillonnage2.h"


int main(int argc, char **argv)
{
    Arguments mes_arguments = utilisation_argument(argc, argv);
    char *filename = mes_arguments.output;
    char *input = mes_arguments.input;
    char *sample_factors = mes_arguments.sample_factors;
    bool couleur = mes_arguments.couleur;
    bool verbose = mes_arguments.verbose;
    bool progression = mes_arguments.progression;

    uint8_t* tableau_coeffs_sous_echantillonage = echantillonage(sample_factors);
    uint8_t h1 = tableau_coeffs_sous_echantillonage[0];
    uint8_t v1 = tableau_coeffs_sous_echantillonage[1];
    uint8_t h2 = tableau_coeffs_sous_echantillonage[2];
    uint8_t v2 = tableau_coeffs_sous_echantillonage[3];
    uint8_t h3 = tableau_coeffs_sous_echantillonage[4];
    uint8_t v3 = tableau_coeffs_sous_echantillonage[5];

    data_frame our_datas = Lecture_Init(input);
    affiche_data(our_datas, mes_arguments);

    FILE *fptr = fopen(filename, "wb");
    ecriture_en_tete(fptr, our_datas.nb_ligne, our_datas.nb_colonne, tableau_coeffs_sous_echantillonage, couleur);

    uint8_t *RLE;
    int16_t prec_Y = 0;
    int16_t prec_Cb = 0;
    int16_t prec_Cr = 0;
    uint32_t compteur = 0;
    uint8_t *resultat_final;
    uint64_t numero_MCU = 0;
    
    ecritureSOS *ecr = malloc(sizeof(ecritureSOS));
    ecr->nb = 0;
    ecr->compteur = 7;
    uint8_t ***liste_MCU = allocation(h1, v1);

    if ((h1 != 1 || v1 != 1) && couleur == true)
    {
        uint32_t nb_MCU_ligne = ceil(((float) our_datas.nb_ligne) / MCU_TAILLE);
        uint32_t nb_MCU_colonne = ceil(((float) our_datas.nb_colonne) / MCU_TAILLE);
        if (verbose)
        {
            printf("h1 : %d v1  : %d\n", h1, v1);
            printf("h2 : %d v2  : %d\n", h2, v2);
            printf("h3 : %d v3  : %d\n", h3, v3);
            printf("nb_MCU_ligne %d nb_MCU_colonne %d\n", nb_MCU_ligne,nb_MCU_colonne);
            printf("%d\n", nb_MCU_colonne*nb_MCU_ligne);
        }
        
        uint64_t* tab_lecture_mcu = ensemble_valeur(tableau_coeffs_sous_echantillonage, our_datas); //ordre des mcu a lire 
        uint32_t i = 0;
        while (tab_lecture_mcu[i] != 2147483648)
        {
            if(progression)
            {
                affiche_progression(our_datas.nb_MCU, i);
            }
            for (uint8_t j = 0; j < h1 * v1; j++)
            { 
                //on remplit comme il faut la liste des MCU
                MCU_RGB* mcu = Read_File(our_datas, tab_lecture_mcu[i + j]);
                if (verbose)
                {
                    printf("MCU_RGB numéro %ld: \n", numero_MCU);
                    for (uint8_t i = 0; i < MCU_TAILLE; i++)
                    {
                        for (uint8_t j = 0; j < MCU_TAILLE; j++)
                        {
                            printf("%02x\t", mcu->tab[i][j].R);
                        }
                        printf("\n");
                    }
                }

                uint8_t ***mcu_YCbCr = conversionRGB_2_YCrCb_MCU(mcu);
                free(mcu);
                for (uint8_t k = 0; k < MCU_TAILLE; k++)
                {
                    for (uint8_t l = 0; l < MCU_TAILLE; l++)
                    {
                        liste_MCU[j][k][l] = mcu_YCbCr[0][k][l];
                        liste_MCU[1 * h1 * v1 + j][k][l] = mcu_YCbCr[1][k][l];
                        liste_MCU[2 * h1 * v1 + j][k][l] = mcu_YCbCr[2][k][l];
                    }
                    free(mcu_YCbCr[0][k]);
                    free(mcu_YCbCr[1][k]);
                    free(mcu_YCbCr[2][k]);
                }
                free(mcu_YCbCr[0]);
                free(mcu_YCbCr[1]);
                free(mcu_YCbCr[2]);
                free(mcu_YCbCr);
            }
            uint8_t ***liste_echantillonnee = echantillonnage_complet_depuis_YCbCr(liste_MCU, tableau_coeffs_sous_echantillonage);
            
            for (uint8_t k = 0; k < h1 * v1; k++)
            {
                int16_t** img_Y_DCT = dct(liste_echantillonnee[k]);
                int16_t* img_Y_ZigZag = zigzag_matrice1(img_Y_DCT);
                int16_t* img_Y_quantifie = quotient_qtable_Y(img_Y_ZigZag);
                RLE = codage_AC_RLE(img_Y_quantifie);
                resultat_final = codage_total_AC_DC_Y(RLE, prec_Y, img_Y_quantifie, verbose);
                ecr = ecrire_SOS_contenu(fptr, resultat_final, ecr);
                prec_Y = img_Y_quantifie[0];

                for (uint8_t b=0;b<MCU_TAILLE;b++){
                    free(img_Y_DCT[b]);
                    free(liste_echantillonnee[k][b]);
                }
                free(img_Y_DCT);
                free(img_Y_ZigZag);
                free(img_Y_quantifie);
                free(RLE);
                free(resultat_final);
                free(liste_echantillonnee[k]);
            }
            if(couleur)
            {
                for (uint8_t k = 0; k < h2 * v2; k++)
                {
                    int16_t **img_Cb_DCT = dct(liste_echantillonnee[k + h1 * v1]);//tableau_MCU[nb_Cb]);
                    int16_t *img_Cb_ZigZag = zigzag_matrice1(img_Cb_DCT);
                    int16_t *img_Cb_quantifie = quotient_qtable_CbCr(img_Cb_ZigZag);
                    RLE = codage_AC_RLE(img_Cb_quantifie);
                    resultat_final = codage_total_AC_DC_CbCr(RLE, prec_Cb, img_Cb_quantifie, verbose);
                    ecr = ecrire_SOS_contenu(fptr, resultat_final, ecr);
                    prec_Cb = img_Cb_quantifie[0];

                    for (uint8_t b=0;b<MCU_TAILLE;b++){
                        free(img_Cb_DCT[b]);
                        free(liste_echantillonnee[k+h1 * v1][b]);
                    }
                    free(img_Cb_DCT);
                    free(img_Cb_ZigZag);
                    free(img_Cb_quantifie);
                    free(RLE);
                    free(resultat_final);
                    free(liste_echantillonnee[k+h1 * v1]);
                }
                for (uint8_t k = 0; k < h3 * v3; k++)
                {

                    int16_t **img_Cr_DCT = dct(liste_echantillonnee[h1*v1 + h2*v2 + k]);//tableau_MCU[nb_Cb]);
                    int16_t *img_Cr_ZigZag = zigzag_matrice1(img_Cr_DCT);
                    int16_t *img_Cr_quantifie = quotient_qtable_CbCr(img_Cr_ZigZag);
                    RLE = codage_AC_RLE(img_Cr_quantifie);
                    resultat_final = codage_total_AC_DC_CbCr(RLE, prec_Cr, img_Cr_quantifie, verbose);
                    ecr = ecrire_SOS_contenu(fptr, resultat_final, ecr);
                    prec_Cr = img_Cr_quantifie[0];

                    free(img_Cr_ZigZag);
                    free(img_Cr_quantifie);
                    free(RLE);
                    free(resultat_final);
                    for (uint8_t b=0;b<MCU_TAILLE;b++){
                        free(img_Cr_DCT[b]);
                        free(liste_echantillonnee[h1*v1 + h2*v2 + k][b]);
                    }
                    free(img_Cr_DCT);
                    free(liste_echantillonnee[h1*v1 + h2*v2 + k]);
                }
            }
            
            free(liste_echantillonnee);
            i = i + h1 * v1;
            
        }

        
    }
    else
    {
        while (numero_MCU <= our_datas.nb_MCU)
        {
            MCU_RGB* mcu = Read_File(our_datas, numero_MCU);
            if (verbose)
            {
                printf("MCU_RGB numéro %ld: \n", numero_MCU);
                for (uint8_t i = 0; i < MCU_TAILLE; i++)
                {
                    for (uint8_t j = 0; j < MCU_TAILLE; j++)
                    {
                        printf("%02x\t", mcu->tab[i][j].R);
                    }
                    printf("\n");
                }
            }
            
            //CONVERSION
            uint8_t ***mcu_YCbCr = conversionRGB_2_YCrCb_MCU(mcu);
            free(mcu);
            uint8_t **mcu_Y = malloc(MCU_TAILLE * sizeof(uint8_t*));
            uint8_t **mcu_Cb = malloc(MCU_TAILLE * sizeof(uint8_t*));
            uint8_t **mcu_Cr = malloc(MCU_TAILLE * sizeof(uint8_t*));
            
            for (uint8_t i = 0; i < MCU_TAILLE; i++)
            {
                mcu_Y[i] = malloc(MCU_TAILLE * sizeof(uint8_t));
                if (couleur)
                {
                    mcu_Cb[i] = malloc(MCU_TAILLE * sizeof(uint8_t));
                    mcu_Cr[i] = malloc(MCU_TAILLE * sizeof(uint8_t));
                }
                for (uint8_t j = 0; j < MCU_TAILLE; j++)
                {
                    mcu_Y[i][j] = mcu_YCbCr[0][i][j];
                    if (couleur)
                    {
                        mcu_Cb[i][j] = mcu_YCbCr[1][i][j];
                        mcu_Cr[i][j] = mcu_YCbCr[2][i][j];
                    }
                }
                free(mcu_YCbCr[0][i]);
                free(mcu_YCbCr[2][i]);
                free(mcu_YCbCr[1][i]);
            }
            free(mcu_YCbCr[0]);
            free(mcu_YCbCr[1]);
            free(mcu_YCbCr[2]);
            free(mcu_YCbCr);

            if (verbose)
            {
                printf("MCU_YCbCr numéro %ld: \n", numero_MCU);
                for (uint8_t i = 0; i < MCU_TAILLE; i++)
                {
                    for (uint8_t j = 0; j < MCU_TAILLE; j++)
                    {
                        printf("%02x%02x%02x\t\n", mcu_Y[i][j], mcu_Cb[i][j], mcu_Cr[i][j]);
                    }
                    printf("\n"); 
                }

                printf("MCU_Y numéro %ld: \n", numero_MCU);
                for (uint8_t i = 0; i < MCU_TAILLE; i++)
                {
                    for (uint8_t j = 0; j < MCU_TAILLE; j++)
                    {
                        printf("%02x\t", mcu_Y[i][j]);
                    }
                    printf("\n");
                }

                if(couleur)
                {
                    printf("MCU_Cb numéro %ld: \n", numero_MCU);
                    for (uint8_t i = 0; i < MCU_TAILLE; i++)
                    {
                        for (uint8_t j = 0; j < MCU_TAILLE; j++)
                        {
                            printf("%02x\t", mcu_Cb[i][j]);
                        }
                        printf("\n");
                    }
                    printf("MCU_Cr numéro %ld: \n", numero_MCU);
                    for (uint8_t i = 0; i < MCU_TAILLE; i++)
                    {
                        for (uint8_t j = 0; j < MCU_TAILLE; j++)
                        {
                            printf("%02x\t", mcu_Cr[i][j]);
                        }
                        printf("\n");
                    }
                }
            }
            
            int16_t** img_Y_DCT = dct(mcu_Y);
            int16_t* img_Y_ZigZag = zigzag_matrice1(img_Y_DCT);
            int16_t* img_Y_quantifie = quotient_qtable_Y(img_Y_ZigZag);
            RLE = codage_AC_RLE(img_Y_quantifie);
            resultat_final = codage_total_AC_DC_Y(RLE, prec_Y, img_Y_quantifie, verbose);
            ecr = ecrire_SOS_contenu(fptr, resultat_final, ecr);
            prec_Y = img_Y_quantifie[0];
            free(RLE);
            free(resultat_final);

            if (couleur)
            { // on fait Cb et Cr
                // Partie Cb
                int16_t **img_Cb_DCT = dct(mcu_Cb);//tableau_MCU[nb_Cb]);
                int16_t *img_Cb_ZigZag = zigzag_matrice1(img_Cb_DCT);
                int16_t *img_Cb_quantifie = quotient_qtable_CbCr(img_Cb_ZigZag);
                RLE = codage_AC_RLE(img_Cb_quantifie);
                resultat_final = codage_total_AC_DC_CbCr(RLE, prec_Cb, img_Cb_quantifie, verbose);
                ecr = ecrire_SOS_contenu(fptr, resultat_final, ecr);
                prec_Cb = img_Cb_quantifie[0];
                for (uint8_t b=0;b<MCU_TAILLE;b++){
                    free(img_Cb_DCT[b]);
                }
                free(img_Cb_DCT);
                free(img_Cb_ZigZag);
                free(img_Cb_quantifie);
                free(RLE);
                free(resultat_final);


                // Partie Cr
                int16_t **img_Cr_DCT = dct(mcu_Cr);//tableau_MCU[nb_Cr]);
                int16_t *img_Cr_ZigZag = zigzag_matrice1(img_Cr_DCT);
                int16_t *img_Cr_quantifie = quotient_qtable_CbCr(img_Cr_ZigZag);
                RLE = codage_AC_RLE(img_Cr_quantifie);
                resultat_final = codage_total_AC_DC_CbCr(RLE, prec_Cr, img_Cr_quantifie, verbose);
                ecr = ecrire_SOS_contenu(fptr, resultat_final, ecr);
                prec_Cr = img_Cr_quantifie[0];
                for (uint8_t b=0;b<MCU_TAILLE;b++){
                    free(img_Cr_DCT[b]);
                }
                free(img_Cr_DCT);
                free(img_Cr_ZigZag);
                free(img_Cr_quantifie);
                free(RLE);
                free(resultat_final);
            }
            if(progression)
            {
                affiche_progression(our_datas.nb_MCU, numero_MCU);
            }
            numero_MCU++;
            compteur++;     
        
            for (uint32_t i = 0; i < MCU_TAILLE; i++)
            {
                free(mcu_Y[i]);
                if (couleur){
                    free(mcu_Cb[i]);
                    free(mcu_Cr[i]);
                }
            }
            free(mcu_Y);
            free(mcu_Cb);
            free(mcu_Cr);
            for (uint8_t b=0;b<MCU_TAILLE;b++){
                free(img_Y_DCT[b]);
            }
            free(img_Y_DCT);
            free(img_Y_ZigZag);
            free(img_Y_quantifie);
        }
    }
    Fermeture_fichier(our_datas);
    fwrite(&(ecr->nb), sizeof(uint8_t), 1, fptr);
    free(ecr);
    ecrire_fin(fptr);
    fclose(fptr);
    affichage_fin(input, filename);
    free(filename);
    liberation(liste_MCU, h1, v1);
    free(tableau_coeffs_sous_echantillonage);
    return 0;
}