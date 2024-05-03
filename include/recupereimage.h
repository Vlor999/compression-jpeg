#ifndef _RECUPEREIMAGE_H
#define _RECUPEREIMAGE_H
#include <stdio.h>
#include <stdint.h>


struct imagePGM{
    uint32_t col;
    uint32_t ligne;
    int8_t max;
    uint8_t** tab;
};
typedef struct imagePGM imagePGM;



/**
 * @brief recupere l'image au format pgm 
 *
 * @param file nom du fichier pgm
 * @return image de type imagePGM
 */

imagePGM *recupereimage(char* file);

#endif
