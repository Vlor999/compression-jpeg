// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>
// #include "../include/conversionRGB.h"
// #include "../include/recupereimage.h"
// #include "../include/conversionRGB.h"
// #include "../include/zigzag.h"
// #include "../include/quantification.h"
// #include "../include/magnetude_dc.h"
// #include "../include/MCU.h"
// #include "../include/DCT.h"
// #include "../include/jpeg_format.h"
// #include "../include/htables.h"
// #include <math.h>
// #include <time.h> 
// #include "../include/qtables.h"
// #include "../include/recup_v2.h"
// #include "../include/ss_echantillonnage2.h"
// #include "../include/option_main.h"

// int main(int argc, char **argv)
// {
//     Arguments mes_arguments = utilisation_argument(argc, argv);
//     char *filename = mes_arguments.output;
//     char *input = mes_arguments.input;
//     char *sample_factors = mes_arguments.sample_factors;
//     bool couleur = mes_arguments.couleur;
//     bool verbose = mes_arguments.verbose;

//     if (!input)
//     {
//         return 1;
//     }

//     if(sample_factors == NULL)
//     {
//         sample_factors = "1x1,1x1,1x1";
//     }
//     uint8_t* tableau_coeffs_sous_echantillonage = echantillonage(sample_factors);
//     uint8_t h1 = tableau_coeffs_sous_echantillonage[0];
//     uint8_t v1 = tableau_coeffs_sous_echantillonage[1];
//     uint8_t h2 = tableau_coeffs_sous_echantillonage[2];
//     uint8_t v2 = tableau_coeffs_sous_echantillonage[3];
//     uint8_t h3 = tableau_coeffs_sous_echantillonage[4];
//     uint8_t v3 = tableau_coeffs_sous_echantillonage[5];



//     printf("input : %s\n", input);
//     printf("output : %s\n", filename);
//     printf("sample_factors : %s\n", sample_factors);
//     printf("couleur : %d\n", couleur);
//     printf("verbose : %d\n", verbose);

//     data_frame our_datas = Lecture_Init(input);
//     printf("data_frame : \n");
//     printf("nb_colonne : %d\n", our_datas.nb_colonne);
//     printf("nb_ligne : %d\n", our_datas.nb_ligne);
//     printf("nb_MCU : %d\n", our_datas.nb_MCU);
//     printf("maximum_value : %d\n", our_datas.maximum_value);
//     printf("header : %d\n", our_datas.header);
//     printf("isRGB : %d\n", our_datas.isRGB);
 

//     FILE *fptr = fopen(filename, "wb");
//     ecrire_debut(fptr);
//     ecrire_commentaire_SOS_PC(fptr);
//     ecrire_qtable(fptr, quantification_table_Y, quantification_table_CbCr, couleur);
//     ecrire_SOF(fptr, our_datas.nb_ligne, our_datas.nb_colonne, NULL,couleur); // faire en sorte qu'il change en fonction de l'image
//     ecrire_htable(fptr, htables_nb_symb_per_lengths, couleur);
//     ecrire_SOS_en_tete(fptr, couleur);


//     int16_t prec_Y = 0;
//     int16_t prec_Cb = 0;
//     int16_t prec_Cr = 0;
//     ecritureSOS *ecr = malloc(sizeof(ecritureSOS));
//     ecr->nb = 0;
//     uint8_t *RLE;
//     uint8_t *resultat_final;
//     ecr->compteur = 7;
//     uint32_t compteur;
//     uint64_t numero_MCU = 1;
//     printf("nb_MCU : %d\n", our_datas.nb_MCU);
//     while (numero_MCU <= our_datas.nb_MCU)
//     {
//         //printf("MCU numéro %d\n", numero_MCU);
//         //LECTURE
//             MCU_RGB* mcu = Read_File(our_datas, numero_MCU);
//             if (verbose)
//             {
//                 printf("MCU_RGB numéro %d: \n", numero_MCU);
//                 for (int i = 0; i < MCU_TAILLE; i++)
//                 {
//                     for (int j = 0; j < MCU_TAILLE; j++)
//                     {
//                         printf("%02x\t", mcu->tab[i][j].R);
//                     }
//                     printf("\n");
//                 }
//             }
            
//             //CONVERSION
//             uint8_t ***mcu_YCbCr = conversionRGB_2_YCrCb_MCU(mcu);
//             uint8_t **mcu_Y = malloc(MCU_TAILLE*sizeof(uint8_t*));
//             uint8_t **mcu_Cb =malloc(MCU_TAILLE*sizeof(uint8_t*));
//             uint8_t **mcu_Cr =malloc(MCU_TAILLE*sizeof(uint8_t*));
            
//             for (int i = 0; i < MCU_TAILLE; i++)
//                 {
//                     mcu_Y[i]=malloc(MCU_TAILLE*sizeof(uint8_t));
//                     mcu_Cb[i]=malloc(MCU_TAILLE*sizeof(uint8_t));
//                     mcu_Cr[i]=malloc(MCU_TAILLE*sizeof(uint8_t));
//                     for (int j = 0; j < MCU_TAILLE; j++)
                    
//                     {
                        
//                         mcu_Y[i][j] = mcu_YCbCr[0][i][j];
//                         mcu_Cb[i][j] = mcu_YCbCr[1][i][j];
//                         mcu_Cr[i][j] = mcu_YCbCr[2][i][j];
//                     }
//                 }
//             if (verbose)
//             {
//                 printf("MCU_YCbCr numéro %d: \n", numero_MCU);
//                 for (int i = 0; i < MCU_TAILLE; i++)
//                 {
                    
//                     for (int j = 0; j < MCU_TAILLE; j++)
//                     {
//                         printf("test\n");
//                         //printf("%02x%02x%02x\t\n", mcu_Y[i][j], mcu_Cb[i][j], mcu_Cr[i][j]);
//                     }
//                     printf("\n"); 
//                 }
//             }
//             if (verbose)
//             {
//                 printf("MCU_Y numéro %d: \n", numero_MCU);
//                 for (int i = 0; i < MCU_TAILLE; i++)
//                 {
//                     for (int j = 0; j < MCU_TAILLE; j++)
//                     {
//                         printf("%02x\t", mcu_Y[i][j]);
//                     }
//                     printf("\n");
//                 }
//                 if(couleur)
//                 {
//                     printf("MCU_Cb numéro %d: \n", numero_MCU);
//                     for (int i = 0; i < MCU_TAILLE; i++)
//                     {
//                         for (int j = 0; j < MCU_TAILLE; j++)
//                         {
//                             printf("%02x\t", mcu_Cb[i][j]);
//                         }
//                         printf("\n");
//                     }
//                     printf("MCU_Cr numéro %d: \n", numero_MCU);
//                     for (int i = 0; i < MCU_TAILLE; i++)
//                     {
//                         for (int j = 0; j < MCU_TAILLE; j++)
//                         {
//                             printf("%02x\t", mcu_Cr[i][j]);
//                         }
//                         printf("\n");
//                     }
//                 }
//             }
//             //MCU_YCbCr *tableau_MCU = fonction(willem);
//             //for (uint8_t nb_Y=0;nb_Y<tableau_coeffs_sous_echantillonage[0]*tableau_coeffs_sous_echantillonage[1];nb_Y++){
//                 //if (tableau_MCU[nb_Y] != NULL){
//                     int16_t** img_Y_DCT = dct(mcu_Y);
//                     int16_t* img_Y_ZigZag = zigzag_matrice1(img_Y_DCT);
//                     int16_t* img_Y_quantifie = quotient_qtable_Y(img_Y_ZigZag);
//                     RLE = codage_AC_RLE(img_Y_quantifie);
//                     resultat_final = codage_total_AC_DC_Y(RLE, prec_Y, img_Y_quantifie, verbose);
//                     ecr = ecrire_SOS_contenu(fptr, resultat_final, ecr);
//                     prec_Y = img_Y_quantifie[0];
//                     //numero_MCU++;
//                 //}
//             //}

//             if (couleur)
//                 { // on fait Cb et Cr
//                     // Partie Cb
//                     //for (uint8_t nb_Cb=0;nb_Cb<tableau_coeffs_sous_echantillonage[2]*tableau_coeffs_sous_echantillonage[3];nb_Cb++){
//                       //  if ((tableau_MCU[tableau_coeffs_sous_echantillonage[0]*tableau_coeffs_sous_echantillonage[1]+nb_Cb]) != NULL){
//                             //uint16_t **mcu_Cb_ech = ss_echantillonnage(mcu_Cb, h2, v2);
//                             int16_t **img_Cb_DCT = dct(mcu_Cb);//tableau_MCU[nb_Cb]);
//                             int16_t *img_Cb_ZigZag = zigzag_matrice1(img_Cb_DCT);
//                             int16_t *img_Cb_quantifie = quotient_qtable_CbCr(img_Cb_ZigZag);
//                             RLE = codage_AC_RLE(img_Cb_quantifie);
//                             resultat_final = codage_total_AC_DC_CbCr(RLE, prec_Cb, img_Cb_quantifie, verbose);
//                             ecr = ecrire_SOS_contenu(fptr, resultat_final, ecr);
//                             prec_Cb = img_Cb_quantifie[0];
//                       //      numero_MCU++;
//                         //}
//                     //}

//                     // Partie Cr
//                     //for (uint8_t nb_Cr=0;nb_Cr<tableau_coeffs_sous_echantillonage[4]*tableau_coeffs_sous_echantillonage[5];nb_Cr++){
//                         //if ((tableau_MCU[tableau_coeffs_sous_echantillonage[0]*tableau_coeffs_sous_echantillonage[1]+tableau_coeffs_sous_echantillonage[2]*tableau_coeffs_sous_echantillonage[3]+nb_Cr]) != NULL){
//                             //uint16_t **mcu_Cr_ech = ss_echantillonnage(mcu_Cr, h3, v3);
//                             int16_t **img_Cr_DCT = dct(mcu_Cr);//tableau_MCU[nb_Cr]);
//                             int16_t *img_Cr_ZigZag = zigzag_matrice1(img_Cr_DCT);
//                             int16_t *img_Cr_quantifie = quotient_qtable_CbCr(img_Cr_ZigZag);
//                             RLE = codage_AC_RLE(img_Cr_quantifie);
//                             resultat_final = codage_total_AC_DC_CbCr(RLE, prec_Cr, img_Cr_quantifie, verbose);
//                             ecr = ecrire_SOS_contenu(fptr, resultat_final, ecr);
//                             prec_Cr = img_Cr_quantifie[0];
//                             //numero_MCU++;
//                         //}
//                     //}
//                 }
//         numero_MCU++;
//         compteur++;     
        
//         free(mcu);
//         free(mcu_YCbCr);
//         for (uint32_t i = 0; i < MCU_TAILLE; i++)
//         {
//             free(mcu_Y[i]);
//             free(mcu_Cb[i]);
//             free(mcu_Cr[i]);
//         }
//         free(mcu_Y);
//         free(mcu_Cb);
//         free(mcu_Cr);
//         free(img_Y_DCT);
//         free(img_Y_ZigZag);
//         free(img_Y_quantifie);
//         free(RLE);
//         free(resultat_final);

//     }

//     Fermeture_fichier(our_datas);
//     fwrite(&(ecr->nb), sizeof(uint8_t), 1, fptr);
//     ecrire_fin(fptr);
//     fclose(fptr);
//     printf("fini \n");
// }