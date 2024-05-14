#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/conversionRGB.h"

void probleme_echantillonnage();

bool verif_rectriction(uint8_t h1,uint8_t v1,uint8_t h2,uint8_t v2,uint8_t h3,uint8_t v3);

uint8_t *echantillonage(char* sample_factors);


uint8_t** ss_echantillonnage(uint8_t** tableau, uint8_t h, uint8_t v);

uint8_t** concat_matrice(uint8_t*** liste_matrice, uint8_t h, uint8_t v);

uint8_t*** sous_echantillonnage_CbCr(uint8_t*** liste_matrice, uint8_t h1, uint8_t v1, uint8_t h, uint8_t v);

MCU_YCbCr* sous_echantilonnage(uint8_t* value, data_frame our_datas, uint64_t numero_premiere_mcu);
