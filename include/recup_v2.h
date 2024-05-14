#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/conversionRGB.h"

typedef struct data_frame
{
    uint16_t nb_colonne;
    uint16_t nb_ligne;
    uint32_t nb_MCU;
    uint16_t maximum_value;
    uint8_t header;
    bool isRGB;
    FILE* file;
    uint32_t sous_matrice_par_ligne;
    uint32_t sous_matrice_par_colonne;
} data_frame;



imagePGM_RGB* LecturePPM(const char* filename);

/****/

data_frame Lecture_Init(const char* filename);

MCU_RGB* Read_File(data_frame data, uint64_t number);

void Fermeture_fichier(data_frame data);
