#include <stdio.h>
#include <stdint.h>


typedef struct imagePGM{
    int32_t col;
    int32_t ligne;
    int32_t max;
    uint8_t** tab;
}imagePGM;

imagePGM* recupereimage(char* file);
