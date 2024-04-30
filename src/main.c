#include "conversionRGB.h"
#include "recupereimage.h"
#include "MCU.h"
#include "DCT.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int main(){
    imagePGM *img = recupereimage("src/our_images/alea_image1.pgm"); // cest bon 
    printf("unrignerigreughre\n");
    for (int i= 0; i < img->col; i++){
        for (int j = 0; j < img->ligne; j ++){
            printf("%d ", img->tab[i][j]);   
        }
        printf("\n");
    }
    Triplet_RGB r;
    r.G = 11;
    r.B = 10;
    r.R = 10;
    //Triplet_Y y = conversionRGB(r);
    // printf("%f %f %f\n", y.Y,y.Cb,y.Cr);
    //Triplet_Y **triplet_y = conversiontotale(img);

}
