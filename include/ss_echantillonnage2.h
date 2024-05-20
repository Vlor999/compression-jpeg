
#ifndef _SS_ECHANTILLONNAGE2_H
#define _SS_ECHANTILLONNAGE2_H
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "conversionRGB.h"
#include "recup_v2.h"

uint64_t* sous_echantilonnage(uint8_t* value, data_frame our_datas, uint64_t numero_premiere_mcu);

uint64_t* ensemble_valeur(uint8_t* value, data_frame our_datas);


// Crée une plus grosse matrice dans la liste de matrices donnée 
uint8_t** concat_matrice(uint8_t*** liste_matrice, uint8_t h, uint8_t v,uint8_t decalage);


// Renvoie la liste sous echantillonnée de taille h*v
uint8_t*** sous_echantillonnage_CbCr(uint8_t** grande_matrice, uint8_t h1, uint8_t v1, uint8_t h, uint8_t v) ;

//Renvoie les Y Cb Cr sous forme de liste, il suffit ensuite de les mettre dans le flux 
uint8_t ***echantillonnage_complet_depuis_YCbCr(uint8_t ***liste_matrice,uint8_t *facteurs);//dans liste_matrice tous les Y puis tous les Cb puis tous les Cr

//Renvoie les facteurs sous forme de liste
uint8_t *echantillonage(char* sample_factors);

//Vérifie les restrictions
bool verif_rectriction(uint8_t h1,uint8_t v1,uint8_t h2,uint8_t v2,uint8_t h3,uint8_t v3);

void probleme_echantillonnage();

void free_tab_echantillonnee(Triplet_YCbCr** tab);




#endif