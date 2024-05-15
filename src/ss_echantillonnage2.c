#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "../include/conversionRGB.h"
#include "../include/recup_v2.h"

uint8_t** concat_matrice(uint8_t*** liste_matrice, uint8_t h, uint8_t v,uint8_t decalage)
{
    uint8_t** matrice_finale = malloc(8 * v * sizeof(uint8_t*));
    for (uint8_t i = 0; i < 8 * v; i++)
    {
        matrice_finale[i] = malloc(8 * h * sizeof(uint8_t));
    }
    
    uint8_t compteur_v = 0;
    uint8_t compteur_h = 0;
    uint8_t compteur = 0;
    while (compteur < h*v){
        
        for(uint8_t i = 0; i < 8; i++)
        {
            for(uint8_t j = 0; j < 8; j++)
            {
                matrice_finale[compteur_v * 8 + i][compteur_h * 8 + j] = liste_matrice[compteur+decalage][i][j];
            }
            //printf("\n");

        }
        
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
        result[i]=malloc(8*sizeof(uint8_t*));
        for (uint8_t j=0;j<8;j++){
            result[i][j] = malloc(8*sizeof(uint8_t));
        }
    }
    uint8_t pas_v = v1/v;
    uint8_t pas_h = h1/h;
    uint8_t compteur_v = 0;
    uint8_t compteur_h = 0;
    uint8_t compteur = 0;
    for (uint16_t i=0;i<v1*8;i=i+pas_v){
        for (uint16_t j=0;j<h1*8;j=j+pas_h){
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
            
            if (compteur_h  == 7 && compteur_v  == 7){
                compteur++;
                compteur_v=0;
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
    return result;
}


uint8_t ***echantillonnage_complet_depuis_YCbCr(uint8_t ***liste_matrice,uint8_t *facteurs){ //dans liste_matrice tous les Y puis tous les Cb puis tous les Cr

    // uint8_t ***resultat_Cb = malloc((facteurs[3]*facteurs[2])*sizeof(uint8_t**));
    // for (uint8_t l=0;l<facteurs[3]*facteurs[2];l++){
    //     resultat_Cb[l]=malloc(8*sizeof(uint8_t*));
    //     for (uint8_t i=0;i<8;i++){
    //         resultat_Cb[l][i]=malloc(8*sizeof(uint8_t));
    //         for (uint8_t j=0;j<8;j++){
    //             resultat_Cb[l][i][j] = liste_matrice[l+facteurs[0]*facteurs[1]][i][j];
    //         }
    //     }
    // }
    printf("inter \n");
    uint8_t **temp_Cb = concat_matrice(liste_matrice,facteurs[0],facteurs[1],facteurs[1]*facteurs[0]);
    for (int i=0;i<8*facteurs[1];i++){
        for (int j=0;j<8*facteurs[0];j++){
            printf("%d\t", temp_Cb[i][j]);
        }
        printf("\n");
    }
    printf("\n resultat CB\n");
    uint8_t ***liste_Cb = sous_echantillonnage_CbCr(temp_Cb,facteurs[0],facteurs[1],facteurs[2],facteurs[3]);
    for (int i=0;i<facteurs[3]*facteurs[2];i++){
        for (int j=0;j<8;j++){
            for (int k=0;k<8;k++){
            printf("%d\t", liste_Cb[i][j][k]);
            }
            printf("\n");
        }
        
    }
    printf("\n");
    printf("fini Cb\n");
    
    // uint8_t ***resultat_Cr = malloc((facteurs[5]*facteurs[4])*sizeof(uint8_t**));
    // for (uint8_t l=0;l<facteurs[5]*facteurs[4];l++){
    //     resultat_Cr[l]=malloc(8*sizeof(uint8_t*));
    //     for (uint8_t i=0;i<8;i++){
    //         resultat_Cr[l][i]=malloc(8*sizeof(uint8_t));
    //         for (uint8_t j=0;j<8;j++){
    //             resultat_Cr[l][i][j] = liste_matrice[l+facteurs[3]*facteurs[2]+facteurs[0]*facteurs[1]][i][j];
    //         }
    //     }
    // }
    uint8_t **temp_Cr = concat_matrice(liste_matrice,facteurs[0],facteurs[1],2*facteurs[1]*facteurs[0]);
    printf("inter \n");
    for (int i=0;i<8*facteurs[1];i++){
        for (int j=0;j<8*facteurs[0];j++){
            printf("%d\t", temp_Cr[i][j]);
        }
        printf("\n");
    }
    uint8_t ***liste_Cr = sous_echantillonnage_CbCr(temp_Cr,facteurs[0],facteurs[1],facteurs[4],facteurs[5]);
    printf("\n resultat CR\n");
    for (int i=0;i<facteurs[3]*facteurs[2];i++){
        for (int j=0;j<8;j++){
            for (int k=0;k<8;k++){
            printf("%d\t", liste_Cr[i][j][k]);
            }
            printf("\n");
        }
        
    }
    printf("\n");
    printf("fini Cr\n");
    

    //TRUC FINAL
    uint8_t ***resultat = malloc((facteurs[0]*facteurs[1]+facteurs[3]*facteurs[2]+facteurs[5]*facteurs[4])*sizeof(uint8_t**));
    for (uint8_t l=0;l<facteurs[0]*facteurs[1];l++){
        resultat[l] = malloc(8*sizeof(uint8_t*));
        for (uint8_t i=0;i<8;i++){
            resultat[l][i]=malloc(8*sizeof(uint8_t));
            for (uint8_t j=0;j<8;j++){
                resultat[l][i][j] = liste_matrice[l][i][j];
            }
        }
    } // On a tous les Y

    for (uint8_t l=0;l<facteurs[3]*facteurs[2];l++){
        resultat[l+facteurs[0]*facteurs[1]] = malloc(8*sizeof(uint8_t*));
        for (uint8_t i=0;i<8;i++){
            resultat[l+facteurs[0]*facteurs[1]][i]=malloc(8*sizeof(uint8_t));
            for (uint8_t j=0;j<8;j++){
                resultat[l+facteurs[0]*facteurs[1]][i][j] = liste_Cb[l][i][j];
            }
        }
    } // On a tous les CB

    for (uint8_t l=0;l<facteurs[5]*facteurs[4];l++){
        resultat[l+facteurs[0]*facteurs[1]+facteurs[3]*facteurs[2]] = malloc(8*sizeof(uint8_t*));
        for (uint8_t i=0;i<8;i++){
            resultat[l+facteurs[0]*facteurs[1]+facteurs[3]*facteurs[2]][i]=malloc(8*sizeof(uint8_t));
            for (uint8_t j=0;j<8;j++){
                resultat[l+facteurs[0]*facteurs[1]+facteurs[3]*facteurs[2]][i][j] = liste_Cb[l][i][j];
            }
        }
    } // On a tous les Cr
    return resultat; 

}
// MCU_YCbCr* sous_echantilonnage(uint8_t* value, data_frame our_datas, uint64_t numero_premiere_mcu)
// {
//     uint8_t h1 = value[0];
//     uint8_t v1 = value[1];
//     uint8_t h2 = value[2];
//     uint8_t v2 = value[3];
//     uint8_t h3 = value[4];
//     uint8_t v3 = value[5];

//     uint32_t sous_matrice_par_ligne = our_datas.nb_colonne / MCU_TAILLE;
//     uint32_t sous_matrice_par_colonne = our_datas.nb_ligne / MCU_TAILLE;

//     uint8_t nombre_MCU_sample = h1 * v1 + h2 * v2 + h3 * v3;
//     uint64_t* liste_numero_MCU = malloc(nombre_MCU_sample * sizeof(uint64_t));
//     uint8_t compteur = 0;
//     uint64_t last_num = 0;
//     bool is_dangerous_horizontal;
//     bool is_dangerous_vertical;
//     uint16_t valeur_fin_ligne = sous_matrice_par_ligne * ((numero_premiere_mcu / sous_matrice_par_ligne) + 1);
//     uint16_t valeur_fin_colonne = sous_matrice_par_colonne * ((numero_premiere_mcu / sous_matrice_par_colonne) + 1);
//     for (uint8_t l = 0; l < v1; l++)
//     {
//         valeur_fin_ligne = valeur_fin_ligne + l * sous_matrice_par_ligne - l;
//         for (uint8_t c = 0; c < h1; c++)
//         {
//             is_dangerous_horizontal = numero_premiere_mcu + c + l * (sous_matrice_par_ligne - 1) >= valeur_fin_ligne;
//             is_dangerous_vertical = numero_premiere_mcu / sous_matrice_par_ligne + l >= our_datas.nb_MCU / sous_matrice_par_colonne;
//             if(is_dangerous_horizontal || is_dangerous_vertical)
//             {
//                 liste_numero_MCU[compteur] = last_num;
//             }
//             else
//             {
//                 liste_numero_MCU[compteur] = numero_premiere_mcu + l * sous_matrice_par_ligne + c;
//                 last_num = liste_numero_MCU[compteur];
//             }
//             compteur++;
//         }
//     }
//     uint8_t*** liste_mcu_Y = malloc(nombre_MCU_sample * sizeof(MCU_YCbCr**));
//     uint8_t*** liste_mcu_Cb = malloc(nombre_MCU_sample * sizeof(MCU_YCbCr**));
//     uint8_t*** liste_mcu_Cr = malloc(nombre_MCU_sample * sizeof(MCU_YCbCr**));

//     for(uint8_t k = 0; k < compteur; k++)
//     {
//         printf("%d\n", liste_numero_MCU[k]);
//         MCU_RGB* matrice = Read_File(our_datas, liste_numero_MCU[k] + 1);
//         uint8_t*** mcu_YCbCr = conversionRGB_2_YCrCb_MCU(matrice);
//         liste_mcu_Y[k] = mcu_YCbCr[0];
//         liste_mcu_Cb[k] = mcu_YCbCr[1];
//         liste_mcu_Cr[k] = mcu_YCbCr[2];
//     }
//     sous_echantillonnage_CbCr(liste_mcu_Cb, h2, v2, h1*v1);
//     sous_echantillonnage_CbCr(liste_mcu_Cr, h3, v3, h1*v1);


// }

// int main(int argc, char **argv)
// {
//     data_frame our_datas = Lecture_Init(argv[1]);
//     uint8_t value[6] = {2, 2, 2, 1, 2, 1};
//     sous_echantilonnage(value, our_datas, atoi(argv[2]));

//     return 0;
// }

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



int main() {
    srand( time( NULL ) );
    char *sample_factors = "1x2,1x1,1x1";
    uint8_t *factors = echantillonage(sample_factors);
    uint8_t ***test=malloc(6*sizeof(uint8_t**));
    test[0] = malloc(8*sizeof(uint8_t*));
    printf("\n Y \n");
    for (int i=0;i<8;i++){
        test[0][i] = malloc(8*sizeof(uint8_t));
        for (int j=0;j<8;j++){
            test[0][i][j] = rand()%10;
            printf("%d\t", test[0][i][j]);
        }
        printf("\n");
    }
    printf("\n");
    test[1] = malloc(8*sizeof(uint8_t*));
    for (int i=0;i<8;i++){
        test[1][i] = malloc(8*sizeof(uint8_t));
        for (int j=0;j<8;j++){
            test[1][i][j] = rand()%10;
            printf("%d\t", test[1][i][j]);
        }
        printf("\n");
    }
    printf("\n CB \n");
    test[2] = malloc(8*sizeof(uint8_t*));
    for (int i=0;i<8;i++){
        test[2][i] = malloc(8*sizeof(uint8_t));
        for (int j=0;j<8;j++){
            test[2][i][j] = rand()%10;
            printf("%d\t", test[2][i][j]);
        }
        printf("\n");
    }
    printf("\n");
    test[3] = malloc(8*sizeof(uint8_t*));
    for (int i=0;i<8;i++){
        test[3][i] = malloc(8*sizeof(uint8_t));
        for (int j=0;j<8;j++){
            test[3][i][j] = rand()%10;
            printf("%d\t", test[3][i][j]);
        }
        printf("\n");
    }
    printf("\n Cr \n");
    test[4] = malloc(8*sizeof(uint8_t*));
    for (int i=0;i<8;i++){
        test[4][i] = malloc(8*sizeof(uint8_t));
        for (int j=0;j<8;j++){
            test[4][i][j] = rand()%10;
            printf("%d\t", test[4][i][j]);
        }
        printf("\n");
    }
    printf("\n");
    test[5] = malloc(8*sizeof(uint8_t*));
    for (int i=0;i<8;i++){
        test[5][i] = malloc(8*sizeof(uint8_t));
        for (int j=0;j<8;j++){
            test[5][i][j] = rand()%10;
            printf("%d\t", test[5][i][j]);
        }
        printf("\n");
    }
    printf("fini\n");
    uint8_t ***retour =  echantillonnage_complet_depuis_YCbCr(test,factors);
    
    // imagePGM_RGB *img = LecturePPM("images/thumbs.ppm"); // nom du fichier a preciser   
    // Triplet_YCbCr** new_image = conversionRGB_2_YCrCb(img); //violent le passage à l'entier ?
    // Triplet_YCbCr** img_echantillonner =  main_ss_echantillonnage(new_image, img->ligne, img->col,facteurs);
    // uint8_t **tab = (uint8_t**)malloc(8*sizeof(uint8_t*));
    // for (int i = 0 ; i < 8; i++)
    // {
    //     tab[i] = (uint8_t*)malloc(8*sizeof(uint8_t));
    //     for (int j = 0; j < 8; j ++)
    //     {
    //         tab[i][j] = i * 8 + j;
    //         printf("%d\t", tab[i][j]);
    //     }
    //     printf("\n");
    // }
    // data_frame data = {8, 8, 1, 255, 0, false, NULL, 8};
    // uint8_t** new_tab = sous_echantillonnage(facteurs, data, 1);
    // for(int i = 0; i < 8; i++)
    // {
    //     for(int j = 0; j < 8; j++)
    //     {
    //         printf("%d ", new_tab[i][j]);
    //     }
    //     printf("\n");
    // }

    return 0;
}
