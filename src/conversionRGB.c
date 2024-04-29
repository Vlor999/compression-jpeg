#include <stdio.h>
#include <stdint.h>
#include "conversionRGB.h"


/**
 * @brief fais conversion de RGB vers YCbCr
 *
 * @param pixel triplet_RGB qui correspond à 1 seul pixel, il faut donc appliquer la fonction sur tous les pixels
 * @return pixel au format YCbCr ou les parametre du triplet (Y, Cb, Cr) sont des floats
 */

Triplet_Y conversionRGB(Triplet_RGB pixel){
    Triplet_Y pixel_YCbCr;
    pixel_YCbCr.Y = 0.299* pixel.R + 0.587* pixel.G + 0.114* pixel.B;
    pixel_YCbCr.Cb = (-0.1687)* pixel.R - 0.3313* pixel.G + 0.5* pixel.B + 128;
    pixel_YCbCr.Cr = 0.5* pixel.R - 0.4187 * pixel.G - 0.0813*pixel.B + 128;
    return pixel_YCbCr;
}