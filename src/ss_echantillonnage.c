#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../include/conversionRGB.h"
#include "../include/recup_v2.h"


MCU_YCbCr* sous_echantilonnage(uint8_t* value, data_frame our_datas, uint64_t numero_premiere_mcu)
{
    uint8_t h1 = value[0];
    uint8_t v1 = value[1];
    uint8_t h2 = value[2];
    uint8_t v2 = value[3];
    uint8_t h3 = value[4];
    uint8_t v3 = value[5];

    uint8_t nombre_MCU_sample = h1 * v1 + h2 * v2 + h3 * v3;
    uint64_t* liste_numero_MCU = malloc(nombre_MCU_sample * sizeof(uint64_t));
    MCU_YCbCr* liste_mcu_YCbCr = malloc(nombre_MCU_sample * sizeof(MCU_YCbCr));
    uint8_t compteur = 0;
    uint64_t last_num = 0;
    bool is_dangerous_horizontal;
    bool is_dangerous_vertical;
    for (uint8_t l = 0; l < h1; l++)
    {
        for (uint8_t c = 0; c < v1; c++)
        {
            is_dangerous_horizontal = (numero_premiere_mcu % (our_datas.sous_matrice_par_ligne + 1)) + l > our_datas.sous_matrice_par_ligne;  
            is_dangerous_vertical = (numero_premiere_mcu % (our_datas.sous_matrice_par_colonne + 1)) + c > our_datas.sous_matrice_par_colonne;
            if(is_dangerous_horizontal || is_dangerous_vertical)
            {
                liste_numero_MCU[compteur] = last_num;
            }
            else
            {
                liste_numero_MCU[compteur] = numero_premiere_mcu + l * our_datas.sous_matrice_par_ligne + c;
                last_num = liste_numero_MCU[compteur];
            }
            compteur++;
        }
    }
    for(uint8_t i = 0; i < compteur; i++)
    {
        printf("%d\n", liste_numero_MCU[i]);
    }
}

int main()
{
    uint8_t value[6] = {2, 2, 2, 2, 2, 2};
    data_frame our_datas = {64, 64, 64, 255, 0, false, NULL, 8, 8};
    sous_echantilonnage(value, our_datas, 1);
    return 0;
}

// typedef struct data_frame
// {
//     uint16_t nb_colonne;
//     uint16_t nb_ligne;
//     uint32_t nb_MCU;
//     uint16_t maximum_value;
//     uint8_t header;
//     bool isRGB;
//     FILE* file;
//     uint32_t sous_matrice_par_ligne;
//     uint32_t sous_matrice_par_colonne;
// } data_frame;

Triplet_YCbCr** ss_echantillonnage422(Triplet_YCbCr** tableau, uint32_t lignes, uint32_t col, bool facteurs_hor){ //le facteurs_hor definie si on echantillonne horizontalement ou verticalement
    Triplet_YCbCr** tab_echantillonnee = malloc(lignes * sizeof(Triplet_YCbCr*));
    float valeur_Cb;
    float valeur_Cr;
    for (uint32_t i = 0; i < lignes; i++)
    {
        tab_echantillonnee[i] = malloc(col * sizeof(Triplet_YCbCr));
        for (uint32_t j = 0; j < col; j++)
        {
            if (!facteurs_hor){
                if (j%2 == 0){
                    valeur_Cb = tableau[i][j].Cb;
                    valeur_Cr = tableau[i][j].Cr;
                    tab_echantillonnee[i][j].Cb = 0;
                    tab_echantillonnee[i][j].Cr = 0;
                    tab_echantillonnee[i][j].Y = tableau[i][j].Y;
                }
                else if (j > 0){
                    tab_echantillonnee[i][j].Cb = (tableau[i][j].Cb + valeur_Cb)/2 ;
                    tab_echantillonnee[i][j].Cr = (tableau[i][j].Cr + valeur_Cr)/2 ;
                    tab_echantillonnee[i][j].Y = tableau[i][j].Y;
                    valeur_Cb = 0;
                    valeur_Cr = 0;
                }
            }
            else{
                if (i%2 == 0){
                    valeur_Cb = tableau[i][j].Cb;
                    valeur_Cr = tableau[i][j].Cr;
                    tab_echantillonnee[i][j].Cb = 0;
                    tab_echantillonnee[i][j].Cr = 0;
                    tab_echantillonnee[i][j].Y = tableau[i][j].Y;
                }
                else if (i > 0){
                    tab_echantillonnee[i][j].Cb = (tableau[i][j].Cb + valeur_Cb)/2 ;
                    tab_echantillonnee[i][j].Cr = (tableau[i][j].Cr + valeur_Cr)/2 ;
                    tab_echantillonnee[i][j].Y = tableau[i][j].Y;
                    valeur_Cb = 0;
                    valeur_Cr = 0;
                }
            }
            
        }
    }
    return tab_echantillonnee;

}


Triplet_YCbCr** ss_echantillonnage420(Triplet_YCbCr** tableau, uint32_t lignes, uint32_t col){
    Triplet_YCbCr** tab_echantillonnee = malloc(lignes * sizeof(Triplet_YCbCr*));
    for (uint32_t i = 0; i < lignes; i++)
    {
        tab_echantillonnee[i] = malloc(col * sizeof(Triplet_YCbCr));

        for (uint32_t k=0; k < col; k++)
        {
            if (!(i%2==0)){
                // separation des cas pour faire les moyennes des composantes

                if (i==0 && k == 0){
                    tab_echantillonnee[i][k].Cb = (tableau[i+1][k].Cb + tableau[i][k+1].Cb + tableau[i+1][k+1].Cb)/3 ;
                    tab_echantillonnee[i][k].Cr = (tableau[i+1][k].Cr + tableau[i][k+1].Cr + tableau[i+1][k+1].Cr)/3 ;
                }
                else if(i==0 && k ==col-1){
                    tab_echantillonnee[i][k].Cb = (tableau[i+1][k].Cb + tableau[i][k-1].Cb + tableau[i+1][k-1].Cb)/3 ;
                    tab_echantillonnee[i][k].Cr = (tableau[i+1][k].Cr + tableau[i][k-1].Cr + tableau[i+1][k-1].Cr)/3 ;
                }
                else if(i==lignes-1 && k ==col-1){
                    tab_echantillonnee[i][k].Cb = (tableau[i-1][k].Cb + tableau[i][k-1].Cb + tableau[i-1][k-1].Cb)/3 ;
                    tab_echantillonnee[i][k].Cr = (tableau[i-1][k].Cr + tableau[i][k-1].Cr + tableau[i-1][k-1].Cr)/3 ;
                }
                else if(i==lignes-1 && k ==0){
                    tab_echantillonnee[i][k].Cb = (tableau[i-1][k].Cb + tableau[i][k+1].Cb + tableau[i-1][k+1].Cb)/3 ;
                    tab_echantillonnee[i][k].Cr = (tableau[i-1][k].Cr + tableau[i][k+1].Cr + tableau[i-1][k+1].Cr)/3 ;
                }
                else if (i==0){
                    tab_echantillonnee[i][k].Cb = (tableau[i+1][k].Cb + tableau[i][k+1].Cb + tableau[i+1][k+1].Cb + tableau[i][k-1].Cb  + tableau[i+1][k-1].Cb)/5 ;
                    tab_echantillonnee[i][k].Cr = (tableau[i+1][k].Cr + tableau[i][k+1].Cr + tableau[i+1][k+1].Cr + tableau[i][k-1].Cr  + tableau[i+1][k-1].Cr)/5 ;
                }
                else if (k==0){
                    tab_echantillonnee[i][k].Cb = (tableau[i+1][k].Cb + tableau[i][k+1].Cb + tableau[i+1][k+1].Cb + tableau[i-1][k].Cb + tableau[i-1][k+1].Cb )/5 ;
                    tab_echantillonnee[i][k].Cr = (tableau[i+1][k].Cr + tableau[i][k+1].Cr + tableau[i+1][k+1].Cr + tableau[i-1][k].Cr + tableau[i-1][k+1].Cr )/5 ;
                }
                else if (k == col-1){
                    tab_echantillonnee[i][k].Cb = (tableau[i+1][k].Cb  + tableau[i-1][k].Cb + tableau[i-1][k-1].Cb + tableau[i][k-1].Cb  + tableau[i+1][k-1].Cb)/5 ;
                    tab_echantillonnee[i][k].Cr = (tableau[i+1][k].Cr  + tableau[i-1][k].Cr + tableau[i-1][k-1].Cr + tableau[i][k-1].Cr  + tableau[i+1][k-1].Cr)/5 ;
                }
                else if (i == lignes-1){
                    tab_echantillonnee[i][k].Cb = (tableau[i][k+1].Cb + tableau[i-1][k].Cb + tableau[i-1][k+1].Cb + tableau[i-1][k-1].Cb + tableau[i][k-1].Cb  )/5 ;
                    tab_echantillonnee[i][k].Cr = (tableau[i][k+1].Cr + tableau[i-1][k].Cr + tableau[i-1][k+1].Cr + tableau[i-1][k-1].Cr + tableau[i][k-1].Cr  )/5 ;
                }
                else{
                    tab_echantillonnee[i][k].Cb = (tableau[i+1][k].Cb + tableau[i][k+1].Cb + tableau[i+1][k+1].Cb + tableau[i-1][k].Cb + tableau[i-1][k+1].Cb + tableau[i-1][k-1].Cb + tableau[i][k-1].Cb  + tableau[i+1][k-1].Cb)/8 ;
                    tab_echantillonnee[i][k].Cr = (tableau[i+1][k].Cr + tableau[i][k+1].Cr + tableau[i+1][k+1].Cr + tableau[i-1][k].Cr + tableau[i-1][k+1].Cr + tableau[i-1][k-1].Cr + tableau[i][k-1].Cr  + tableau[i+1][k-1].Cr)/8 ;
                }
            }
            tab_echantillonnee[i][k].Y = tableau[i][k].Y;

        }
        for (uint32_t j = 0; j < col; j++)
        {
            if (i%2 == 0){
                tab_echantillonnee[i][j].Cb = 0;
                tab_echantillonnee[i][j].Cr = 0;
            }
            else{
                if (j%2 == 0){
                    tab_echantillonnee[i][j].Cb = 0;
                    tab_echantillonnee[i][j].Cr = 0;
                }
            }
        }
    }
    return tab_echantillonnee;

}



void free_tab_echantillonnee(Triplet_YCbCr** tab){
    free(tab);
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
    }
    printf("Good\n");
    
    return value;
}



uint8_t** ss_echantillonnage(uint8_t** tableau, uint8_t h, uint8_t v)
{
    uint32_t somme = 0;
    uint8_t** tab_echantillonnee = malloc(8*sizeof(uint8_t*));
    uint8_t compteur = 0;
    for(uint8_t i = 0; i < 8; i++)
    {
        tab_echantillonnee[i] = malloc(8*sizeof(uint8_t));
    }

    for (uint8_t l = 0; l < 8; l += h)
    {
        for(uint8_t c = 0; c < 8; c += v)
        {
            somme = 0;
            compteur = 0;
            for(uint8_t i = 0; i < h; i++)
            {
                for(uint8_t j = 0; j < v; j++)
                {
                    if(l + i < 8 && c + j < 8)
                    {
                        somme += tableau[l + i][c + j];
                        tab_echantillonnee[l + i][c + j] = 0;
                        compteur += 1;
                    }
                }
            }
            tab_echantillonnee[l][c] = somme / compteur;
        }
    }
    return tab_echantillonnee;
}


Triplet_YCbCr** main_ss_echantillonnage(Triplet_YCbCr** tableau, uint32_t lignes, uint32_t col, uint8_t* facteurs){

    uint8_t h1 = facteurs[0];
    uint8_t v1 = facteurs[1];
    uint8_t h2 = facteurs[2];
    uint8_t v2 = facteurs[3];
    uint8_t h3 = facteurs[4];
    uint8_t v3 = facteurs[5];
    if ((h1 == h2) & (h1 == h3) & (v1 == v2) & (v1 == v3)){
        return tableau;
    }
    else if ((h2 == h1/2) & (h3 == h1/2) & (v1 == v2) & (v1 == v3)){ //cas de ss echantillonnage horizontale
        
        Triplet_YCbCr** tableau_echant = ss_echantillonnage422(tableau,lignes,col,true);
        return tableau_echant;
    }
    else if ((h2 == h1) & (h3 == h1) & (v2 == v1/2) & (v2 == v1/2)){ //cas de ss echantillonnage horizontale
        Triplet_YCbCr** tableau_echant = ss_echantillonnage422(tableau,lignes,col,false);
        return tableau_echant;
    }
    else if ((h2 == h1/2) & (h3 == h1/2) & (v2 == v1/2) & (v2 == v1/2)){ //cas de ss echantillonnage horizontale
        Triplet_YCbCr** tableau_echant = ss_echantillonnage420(tableau,lignes,col);
        return tableau_echant;
    }
    // else{
    //     Triplet_YCbCr** tableau_echant = ss_echantillonnage_generale(tableau,lignes,col,facteurs);
    //     return tableau_echant;
    // }
}



// int main() {
//     char *sample_factors = "3x3,3x3,3x1";
//     uint8_t * facteurs;
//     facteurs = echantillonage(sample_factors);
//     // for (int i = 0; i < 6; i++){
//     //     printf("%d ", tab[i]);
//     // }
    
//     // imagePGM_RGB *img = LecturePPM("images/thumbs.ppm"); // nom du fichier a preciser   
//     // Triplet_YCbCr** new_image = conversionRGB_2_YCrCb(img); //violent le passage à l'entier ?
//     // Triplet_YCbCr** img_echantillonner =  main_ss_echantillonnage(new_image, img->ligne, img->col,facteurs);
//     uint8_t **tab = (uint8_t**)malloc(8*sizeof(uint8_t*));
//     for (int i = 0 ; i < 8; i++)
//     {
//         tab[i] = (uint8_t*)malloc(8*sizeof(uint8_t));
//         for (int j = 0; j < 8; j ++)
//         {
//             tab[i][j] = i * 8 + j;
//             printf("%d\t", tab[i][j]);
//         }
//         printf("\n");
//     }
//     data_frame data = {8, 8, 1, 255, 0, false, NULL, 8};
//     uint8_t** new_tab = sous_echantillonnage(facteurs, data, 1);
//     for(int i = 0; i < 8; i++)
//     {
//         for(int j = 0; j < 8; j++)
//         {
//             printf("%d ", new_tab[i][j]);
//         }
//         printf("\n");
//     }
//     return 0;
// }
