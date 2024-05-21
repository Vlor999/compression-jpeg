#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "../include/recup_v2.h"
#include "../include/conversionRGB.h"
#include "../include/ss_echantillonnage2.h"

uint64_t* sous_echantilonnage(uint8_t* value, data_frame our_datas, uint64_t numero_premiere_mcu)
{
    uint8_t h1 = value[0];
    uint8_t v1 = value[1];

    uint32_t sous_matrice_par_ligne = our_datas.nb_colonne / MCU_TAILLE;
    uint32_t sous_matrice_par_colonne = our_datas.nb_ligne / MCU_TAILLE;
    if(our_datas.nb_colonne % MCU_TAILLE != 0)
    {
        sous_matrice_par_ligne = sous_matrice_par_ligne + 1;
    }
    if(our_datas.nb_ligne % MCU_TAILLE != 0)
    {
        sous_matrice_par_colonne = sous_matrice_par_colonne + 1;
    }

    uint8_t nombre_MCU_sample = h1 * v1;
    uint64_t* liste_numero_MCU = malloc(nombre_MCU_sample * sizeof(uint64_t));
    uint8_t compteur = 0;
    uint64_t last_num = 0;
    bool is_dangerous_horizontal;
    bool is_dangerous_vertical;
    uint32_t valeur_fin_ligne = sous_matrice_par_ligne * ((numero_premiere_mcu / sous_matrice_par_ligne) + 1);
    uint16_t nb_ligne = numero_premiere_mcu / sous_matrice_par_ligne;
    for (uint8_t l = 0; l < v1; l++)
    {
        valeur_fin_ligne = (l + 1 + nb_ligne) * sous_matrice_par_ligne - 1;
        for (uint8_t c = 0; c < h1; c++)
        {
            is_dangerous_horizontal = ( numero_premiere_mcu + c > valeur_fin_ligne - l * sous_matrice_par_ligne) || numero_premiere_mcu + c + l * (sous_matrice_par_ligne - 1) > our_datas.nb_MCU;
            is_dangerous_vertical = (numero_premiere_mcu / sous_matrice_par_ligne + l >= our_datas.nb_MCU / sous_matrice_par_ligne);
        
            if(is_dangerous_horizontal || is_dangerous_vertical)
            {
                liste_numero_MCU[compteur] = last_num;
            }
            else
            {
                liste_numero_MCU[compteur] = numero_premiere_mcu + l * sous_matrice_par_ligne + c;
                last_num = liste_numero_MCU[compteur];
            }
            compteur++;
        }
    }
    return liste_numero_MCU;
}

uint64_t* ensemble_valeur(uint8_t* value, data_frame our_datas)
{
    uint64_t numero = 0;
    uint64_t compteur = 0;
    uint8_t h1 = value[0];
    uint8_t v1 = value[1];
    uint64_t* liste_valeur = malloc(our_datas.nb_MCU * sizeof(uint32_t) * h1 * v1);
    uint32_t x = (our_datas.nb_colonne/MCU_TAILLE);
    uint32_t nb_calcul = x / h1;
    if(our_datas.nb_colonne % MCU_TAILLE != 0)
    {
        x = x + 1;
    }
    if(x % h1 != 0)
    {
        nb_calcul = nb_calcul + 1;
    }
    if(h1 == 1)
    {
        nb_calcul = x / h1;
    }
    uint32_t nb = 0;
    // = malloc(h1*v1*sizeof(uint64_t));
    while (numero < our_datas.nb_MCU)
    {
         uint64_t* liste_numero_MCU= sous_echantilonnage(value, our_datas, numero);
        for (uint8_t i = 0; i < h1 * v1; i++)
        {
            liste_valeur[compteur] = liste_numero_MCU[i];
            compteur++;
        }
        
        nb += 1;
        if (nb >= nb_calcul)
        {
            numero = liste_valeur[compteur - 1] + 1;
            nb = 0;
        }
        else
        {
            numero = numero + h1;
        }
    }
    // free(liste_numero_MCU);
    liste_valeur[compteur] = 2147483648;
    return liste_valeur;
}


uint8_t** concat_matrice(uint8_t*** liste_matrice, uint8_t h, uint8_t v, uint8_t decalage)
{
    uint8_t** matrice_finale = malloc(MCU_TAILLE * v * sizeof(uint8_t*)); 
    for (uint8_t i = 0; i < MCU_TAILLE * v; i++)
    {
        matrice_finale[i] = malloc(MCU_TAILLE * h * sizeof(uint8_t));
    }
    
    uint8_t compteur_v = 0;
    uint8_t compteur_h = 0;
    uint8_t compteur = 0;
    // printf("debut matrice \n");
    while (compteur < h*v){
        for(uint8_t i = 0; i < MCU_TAILLE; i++)
        {
            for(uint8_t j = 0; j < MCU_TAILLE; j++)
            {
                matrice_finale[compteur_v * MCU_TAILLE + i][compteur_h * MCU_TAILLE + j] = liste_matrice[compteur+decalage][i][j];
                // printf("%02x\t", matrice_finale[compteur_v * MCU_TAILLE + i][compteur_h * MCU_TAILLE + j]);
            }
            // printf("\n");
        }
        // printf("\n");
        
        if (compteur_h + 1 == h){
            compteur_v ++;
            compteur_h = 0;
            compteur ++;
        }
        else{
            compteur_h ++;
            compteur ++;
        }

    }
    return matrice_finale;
}

uint8_t*** sous_echantillonnage_CbCr(uint8_t** grande_matrice, uint8_t h1, uint8_t v1, uint8_t h, uint8_t v) //pour l'instant je prends la grande matrice
{
    uint8_t ***result = malloc((h*v)*sizeof(uint8_t**));
    for (uint8_t i=0;i<h*v;i++){
        result[i]=malloc(MCU_TAILLE*sizeof(uint8_t*));
        for (uint8_t j=0;j<MCU_TAILLE;j++){
            result[i][j] = malloc(MCU_TAILLE*sizeof(uint8_t));
        }
    }
    uint8_t pas_v = v1/v;
    uint8_t pas_h = h1/h;
    uint8_t compteur_v = 0;
    uint8_t compteur_h = 0;
    uint8_t compteur = 0;
    for (uint16_t i=0;i<v1*MCU_TAILLE;i=i+pas_v){
        for (uint16_t j=0;j<h1*MCU_TAILLE;j=j+pas_h){
            uint16_t somme = 0;
            for (uint16_t k=0;k<pas_v;k++){
                for (uint16_t l=0;l<pas_h;l++){
                    somme+=grande_matrice[i+k][j+l];
                    //printf("%d \n", somme);
                }
            }
            //printf("fef %d %d %d\n",compteur_v,compteur_h, somme/(pas_v*pas_h));
            result[compteur][compteur_v][compteur_h] = somme/(pas_v*pas_h);
            //printf("res %d\n", result[compteur][compteur_v][compteur_h]);
            
            if(h >= v)
            {    
                if (compteur_h  == 7 && compteur == h * v - 1){
                    compteur = 0;
                    compteur_v++;
                    compteur_h=0;
                }
                else if (compteur_h == 7){
                    compteur++;
                    compteur_h=0;
                }
                else{
                    compteur_h++;
                }
            }
            else
            {
                if (compteur_h  == 7 && compteur_v == 7){
                    compteur++;
                    compteur_v = 0;
                    compteur_h=0;
                }
                else if (compteur_h == 7){
                    compteur_v++;
                    compteur_h=0;
                }
                else{
                    compteur_h++;
                }
            }
        }
    }
    return result;
}


uint8_t ***echantillonnage_complet_depuis_YCbCr(uint8_t ***liste_matrice,uint8_t *facteurs){ //dans liste_matrice tous les Y puis tous les Cb puis tous les Cr

    uint8_t **temp_Cb = concat_matrice(liste_matrice,facteurs[0],facteurs[1],facteurs[1]*facteurs[0]);


    uint8_t ***liste_Cb = sous_echantillonnage_CbCr(temp_Cb,facteurs[0],facteurs[1],facteurs[2],facteurs[3]);
    
    for (uint16_t i=0;i<MCU_TAILLE*facteurs[1];i++){
        free(temp_Cb[i]);
    }
    free(temp_Cb);

    uint8_t **temp_Cr = concat_matrice(liste_matrice,facteurs[0],facteurs[1],2*facteurs[1]*facteurs[0]);



    uint8_t ***liste_Cr = sous_echantillonnage_CbCr(temp_Cr,facteurs[0],facteurs[1],facteurs[4],facteurs[5]);
    
    
    for (uint16_t i=0;i<MCU_TAILLE*facteurs[1];i++){
        free(temp_Cr[i]);
    }
    free(temp_Cr);

    //TRUC FINAL
    // printf("\n\nRESULT Y\n");
    uint8_t ***resultat = malloc((facteurs[0]*facteurs[1]+facteurs[3]*facteurs[2]+facteurs[5]*facteurs[4])*sizeof(uint8_t**));
    for (uint8_t l=0;l<facteurs[0]*facteurs[1];l++){
        resultat[l] = malloc(MCU_TAILLE*sizeof(uint8_t*));
        for (uint8_t i=0;i<MCU_TAILLE;i++){
            resultat[l][i]=malloc(MCU_TAILLE*sizeof(uint8_t));
            for (uint8_t j=0;j<MCU_TAILLE;j++){
                resultat[l][i][j] = liste_matrice[l][i][j];
                // printf("%02x\t", liste_matrice[l][i][j]);
            }
            // printf("\n");
        }
        // printf("FIN MCU\n");
    } // On a tous les Y
    // printf("\nRESULT Cb\n");
    for (uint8_t l=0;l<facteurs[3]*facteurs[2];l++){
        resultat[l+facteurs[0]*facteurs[1]] = malloc(MCU_TAILLE*sizeof(uint8_t*));
        for (uint8_t i=0;i<MCU_TAILLE;i++){
            resultat[l+facteurs[0]*facteurs[1]][i]=malloc(MCU_TAILLE*sizeof(uint8_t));
            for (uint8_t j=0;j<MCU_TAILLE;j++){
                resultat[l+facteurs[0]*facteurs[1]][i][j] = liste_Cb[l][i][j];
                // printf("%02x\t", liste_Cb[l][i][j]);
            }
            free(liste_Cb[l][i]);
            // printf("\n");
        }
        free(liste_Cb[l]);
        // printf("FIN MCU\n");
    } // On a tous les CB

    free(liste_Cb);

    // printf("\nRESULT Cr\n");
    for (uint8_t l=0;l<facteurs[5]*facteurs[4];l++){
        resultat[l+facteurs[0]*facteurs[1]+facteurs[3]*facteurs[2]] = malloc(MCU_TAILLE*sizeof(uint8_t*));
        for (uint8_t i=0;i<MCU_TAILLE;i++){
            resultat[l+facteurs[0]*facteurs[1]+facteurs[3]*facteurs[2]][i]=malloc(MCU_TAILLE*sizeof(uint8_t));
            for (uint8_t j=0;j<MCU_TAILLE;j++){
                resultat[l+facteurs[0]*facteurs[1]+facteurs[3]*facteurs[2]][i][j] = liste_Cr[l][i][j];
                // printf("%02x\t", liste_Cr[l][i][j]);
            }
            free(liste_Cr[l][i]);
            // printf("\n");
        }
        free(liste_Cr[l]);
        // printf("FIN MCU\n");
    } // On a tous les Cr

    free(liste_Cr);

    return resultat; 
}

void probleme_echantillonnage()
{
    printf("Probleme d'echantillonnage\n");
    printf("Error: Il faut le bon format : h1xv1,h2xv2,h3xv3 \n");
    printf("La valeur de chaque facteur h ou v doit être comprise entre 1 et 4 \n");
    printf("La somme des produits hi x vi doit etre <= 10 \n");
    printf("Les facteurs d'échantillonnage des chrominances doivent diviser parfaitement ceux de la luminance. \n");
}

bool verif_rectriction(uint8_t h1,uint8_t v1,uint8_t h2,uint8_t v2,uint8_t h3,uint8_t v3)
{
    if (h1 < 1 || h1 > 4 || v1 < 1 || v1 > 4 || h2 < 1 || h2 > 4 || v2 < 1 || v2 > 4 || h3 < 1 || h3 > 4 || v3 < 1 || v3 > 4)
    {
        return false;
    }
    if (h1 * v1 + h2 * v2 + h3 * v3 > 10)
    {
        return false;
    }
    if (h1 % h2 != 0 || h1 % h3 != 0 || v1 % v2 != 0 || v1 % v3 != 0)
    {
        return false;
    }
    return true;
}

uint8_t *echantillonage(char* sample_factors) {
    uint8_t* value = malloc(sizeof(uint8_t)*6);
    for (int i = 0; i < 11; i++){
        if (i%2== 0){
            value[i/2] = ((uint8_t)sample_factors[i]) - 48;
        }
    }
    uint8_t h1 = value[0];
    uint8_t v1 = value[1];
    uint8_t h2 = value[2];
    uint8_t v2 = value[3];
    uint8_t h3 = value[4];
    uint8_t v3 = value[5];
    bool possible = verif_rectriction(h1, v1, h2, v2, h3, v3);
    if (!possible) 
    {
        probleme_echantillonnage();
        free(value);
    }
    
    return value;
}




// int main() {
//     srand( time( NULL ) );
//     char *sample_factors = "1x1,1x1,1x1";
//     uint8_t *factors = echantillonage(sample_factors);
//     uint8_t ***test=malloc(6*sizeof(uint8_t**));
//     test[0] = malloc(MCU_TAILLE*sizeof(uint8_t*));
//     printf("\n Y \n");
//     for (int i=0;i<MCU_TAILLE;i++){
//         test[0][i] = malloc(MCU_TAILLE*sizeof(uint8_t));
//         for (int j=0;j<MCU_TAILLE;j++){
//             test[0][i][j] = rand()%10;
//             printf("%d\t", test[0][i][j]);
//         }
//         printf("\n");
//     }
//     printf("\n Cb \n");
//     test[1] = malloc(MCU_TAILLE*sizeof(uint8_t*));
//     for (int i=0;i<MCU_TAILLE;i++){
//         test[1][i] = malloc(MCU_TAILLE*sizeof(uint8_t));
//         for (int j=0;j<MCU_TAILLE;j++){
//             test[1][i][j] = rand()%10;
//             printf("%d\t", test[1][i][j]);
//         }
//         printf("\n");
//     }
//     printf("\n CR \n");
//     test[2] = malloc(MCU_TAILLE*sizeof(uint8_t*));
//     for (int i=0;i<MCU_TAILLE;i++){
//         test[2][i] = malloc(MCU_TAILLE*sizeof(uint8_t));
//         for (int j=0;j<MCU_TAILLE;j++){
//             test[2][i][j] = rand()%10;
//             printf("%d\t", test[2][i][j]);
//         }
//         printf("\n");
//     }
//     // printf("\n");
//     // test[3] = malloc(MCU_TAILLE*sizeof(uint8_t*));
//     // for (int i=0;i<MCU_TAILLE;i++){
//     //     test[3][i] = malloc(MCU_TAILLE*sizeof(uint8_t));
//     //     for (int j=0;j<MCU_TAILLE;j++){
//     //         test[3][i][j] = rand()%10;
//     //         printf("%d\t", test[3][i][j]);
//     //     }
//     //     printf("\n");
//     // }
//     // printf("\n Cr \n");
//     // test[4] = malloc(MCU_TAILLE*sizeof(uint8_t*));
//     // for (int i=0;i<MCU_TAILLE;i++){
//     //     test[4][i] = malloc(MCU_TAILLE*sizeof(uint8_t));
//     //     for (int j=0;j<MCU_TAILLE;j++){
//     //         test[4][i][j] = rand()%10;
//     //         printf("%d\t", test[4][i][j]);
//     //     }
//     //     printf("\n");
//     // }
//     // printf("\n");
//     // test[5] = malloc(MCU_TAILLE*sizeof(uint8_t*));
//     // for (int i=0;i<MCU_TAILLE;i++){
//     //     test[5][i] = malloc(MCU_TAILLE*sizeof(uint8_t));
//     //     for (int j=0;j<MCU_TAILLE;j++){
//     //         test[5][i][j] = rand()%10;
//     //         printf("%d\t", test[5][i][j]);
//     //     }
//     //     printf("\n");
//     // }
//     // printf("fini\n");
//     uint8_t ***retour =  echantillonnage_complet_depuis_YCbCr(test,factors);
    
//     // imagePGM_RGB *img = LecturePPM("images/thumbs.ppm"); // nom du fichier a preciser   
//     // Triplet_YCbCr** new_image = conversionRGB_2_YCrCb(img); //violent le passage à l'entier ?
//     // Triplet_YCbCr** img_echantillonner =  main_ss_echantillonnage(new_image, img->ligne, img->col,facteurs);
//     // uint8_t **tab = (uint8_t**)malloc(MCU_TAILLE*sizeof(uint8_t*));
//     // for (int i = 0 ; i < MCU_TAILLE; i++)
//     // {
//     //     tab[i] = (uint8_t*)malloc(MCU_TAILLE*sizeof(uint8_t));
//     //     for (int j = 0; j < MCU_TAILLE; j ++)
//     //     {
//     //         tab[i][j] = i * MCU_TAILLE + j;
//     //         printf("%d\t", tab[i][j]);
//     //     }
//     //     printf("\n");
//     // }
//     // data_frame data = {8, 8, 1, 255, 0, false, NULL, 8};
//     // uint8_t** new_tab = sous_echantillonnage(facteurs, data, 1);
//     // for(int i = 0; i < 8; i++)
//     // {
//     //     for(int j = 0; j < 8; j++)
//     //     {
//     //         printf("%d ", new_tab[i][j]);
//     //     }
//     //     printf("\n");
//     // }

//     return 0;
// }
