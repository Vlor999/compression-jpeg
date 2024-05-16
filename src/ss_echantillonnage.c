#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "../include/conversionRGB.h"
#include "../include/recup_v2.h"

uint64_t* sous_echantilonnage(uint8_t* value, data_frame our_datas, uint64_t numero_premiere_mcu)
{
    uint8_t h1 = value[0];
    uint8_t v1 = value[1];
    uint8_t h2 = value[2];
    uint8_t v2 = value[3];
    uint8_t h3 = value[4];
    uint8_t v3 = value[5];

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

    uint8_t nombre_MCU_sample = h1 * v1 + h2 * v2 + h3 * v3;
    uint64_t* liste_numero_MCU = malloc(nombre_MCU_sample * sizeof(uint64_t));
    uint8_t compteur = 0;
    uint64_t last_num = 0;
    bool is_dangerous_horizontal;
    bool is_dangerous_vertical;
    uint16_t valeur_fin_ligne = sous_matrice_par_ligne * ((numero_premiere_mcu / sous_matrice_par_ligne) + 1);
    uint16_t valeur_fin_colonne = sous_matrice_par_colonne * ((numero_premiere_mcu / sous_matrice_par_colonne) + 1);
    for (uint8_t l = 0; l < v1; l++)
    {
        valeur_fin_ligne = valeur_fin_ligne + l * sous_matrice_par_ligne - l;
        for (uint8_t c = 0; c < h1; c++)
        {
            is_dangerous_horizontal = (numero_premiere_mcu + c + l * (sous_matrice_par_ligne - 1) >= valeur_fin_ligne) || numero_premiere_mcu + c + l * (sous_matrice_par_ligne - 1) > our_datas.nb_MCU;
            is_dangerous_vertical = (numero_premiere_mcu / sous_matrice_par_ligne + l >= our_datas.nb_MCU / sous_matrice_par_colonne);
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

uint32_t* ensemble_valeur(uint8_t* value, data_frame our_datas)
{
    uint32_t* liste_valeur = malloc(our_datas.nb_MCU * sizeof(uint32_t) + 1);
    uint32_t numero = 0;
    uint32_t compteur = 0;
    uint8_t h1 = value[0];
    uint8_t v1 = value[1];
    uint32_t x = (our_datas.nb_colonne/MCU_TAILLE);
    uint32_t nb_calcul = x / h1;
    if(our_datas.nb_colonne % MCU_TAILLE != 0)
    {
        x = x + 1;
        nb_calcul = nb_calcul + 1;
    }
    printf("nb_calcul %d\n", nb_calcul);
    uint32_t nb = 0;

    while (numero < our_datas.nb_MCU)
    {
        uint64_t* liste_numero_MCU = sous_echantilonnage(value, our_datas, numero);
        for (uint8_t i = 0; i < h1 * v1; i++)
        {
            liste_valeur[compteur] = liste_numero_MCU[i];
            printf("%d\n", liste_valeur[compteur]);
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
        printf("numero %d\n", numero);
    }
    liste_valeur[compteur] = 2147483648;
    return liste_valeur;
}


int main(char *argv[])
{
    data_frame our_datas = {65, 64, 72, 255, 0, true, NULL};
    uint8_t value[6] = {3, 3, 1, 1, 1, 1};
    // uint64_t* val = sous_echantilonnage(value, our_datas, 69);
    // for (uint8_t i = 0; i < 2; i++)
    // {
    //     printf("%d\n", val[i]);
    // }
    uint32_t* liste_valeur = ensemble_valeur(value, our_datas);
    // uint32_t i = 0;
    // while(liste_valeur[i] != 2147483648)
    // {
    //     printf("%d %d\n", liste_valeur[i], liste_valeur[i+1]);
    //     i+=2;
    // }
    return 0;
}