#include <stdio.h>
#include <stdint.h>

typedef struct Triplet_RGB{
    int8_t R;
    int8_t G;
    int8_t B;
}Triplet_RGB;

typedef struct Triplet_Y{
    float Y;
    float Cb;
    float Cr;
}Triplet_Y;


Triplet_Y conversionRGB(Triplet_RGB pixel);
