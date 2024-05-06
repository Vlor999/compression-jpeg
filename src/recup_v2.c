#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/conversionRGB.h"

// typedef struct Triplet_RGB{
//     uint8_t R;
//     uint8_t G;
//     uint8_t B;
// }Triplet_RGB;


// void libere_image(imagePGM_RGB* image){
//     for (uint32_t i = 0; i < image->ligne; i++)
//     {
//         free(image->tab[i]);
//     }
//     free(image->tab);
//     free(image);
// }


imagePGM_RGB* LecturePPM(const char* filename) 
{
    FILE* file = fopen(filename, "rb");

    if (file == NULL) 
    {
        fprintf(stderr, "Erreur d'ouverture: %s\n", filename);
        return NULL;
    }

    char input[3];
    fscanf(file, "%2s\n", input);

    if (input[0] != 'P' || (input[1] != '6' && input[1] != '5')) 
    {
        fprintf(stderr, "Invalid PPM file format\n");
        fclose(file);
        return NULL;
    }

    int32_t col, ligne, max;
    fscanf(file, "%d %d\n%d\n", &col, &ligne, &max);

    imagePGM_RGB* img = malloc(sizeof(imagePGM_RGB));
    if (img == NULL) 
    {
        fclose(file);
        return NULL;
    }
    
    bool isRGB = input[1] == '6';

    img->col = col;
    img->ligne = ligne;
    img->max = max;

    img->tab = (Triplet_RGB**)malloc(ligne * sizeof(Triplet_RGB*));

    for (int32_t i = 0; i < ligne; i++) 
    {
        img->tab[i] = malloc(col * sizeof(Triplet_RGB));
        for (int32_t j = 0; j < col; j++) 
        {
            if (isRGB) 
            {
                fread(&img->tab[i][j], sizeof(Triplet_RGB), 1, file);
            }
            else 
            {
                uint8_t* pixel = malloc(sizeof(uint8_t));
                fread(pixel, sizeof(uint8_t), 1, file);
                img->tab[i][j].R = *pixel;
                img->tab[i][j].G = *pixel;
                img->tab[i][j].B = *pixel;
            }
        }
    }

    fclose(file);
    return img;
}



// int main(int argc, char* argv[]) {
//     if (argc != 2) 
//     {
//         printf("Mettre sous la forme : %s <filename>\n", argv[0]);
//         return 1;
//     }

//     const char* filename = argv[1];
//     imagePGM* img = LecturePPM(filename);
//     if (!img) {
//         printf("Failed to read PPM file: %s\n", filename);
//         return 1;
//     }

//     for(uint8_t i = 0; i < img->ligne; i++)
//     {
//         for(uint8_t j = 0; j < img->col; j++)
//         {
//             printf("%02x%02x%02x\t", img->tab[i][j].R, img->tab[i][j].G, img->tab[i][j].B);
//         }
//         printf("\n");
//     }

//     libere_image(img);
//     return 0;
// }

