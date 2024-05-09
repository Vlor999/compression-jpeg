#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/conversionRGB.h"
#define MCU_TAILLE 8

typedef struct data_frame
{
    uint16_t nb_colonne;
    uint16_t nb_ligne;
    uint16_t maximum_value;
    uint8_t header;
    bool isRGB;
} data_frame;

typedef struct MCU_RGB
{
    Triplet_RGB tab[MCU_TAILLE][MCU_TAILLE];
}MCU_RGB;


imagePGM_RGB* LecturePPM(const char* filename);

data_frame Lecture_Init(const char* filename);
