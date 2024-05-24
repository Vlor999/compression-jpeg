#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/recupereimage.h"


// typedef struct Triplet_RGB {
//     uint8_t R;
//     uint8_t G;
//     uint8_t B;
// } Triplet_RGB;

// typedef struct imagePGM {
//     int32_t col;
//     int32_t ligne;
//     int8_t max;
//     Triplet_RGB** tab;
// } imagePGM;

// imagePGM* LecturePPM(const char* filename) 
// {
//     FILE* file = fopen(filename, "rb");

//     if (file == NULL) 
//     {
//         fprintf(stderr, "Erreur d'ouverture: %s\n", filename);
//         return NULL;
//     }

//     char input[3];
//     fscanf(file, "%2s\n", input); // Read input number ("P6")

//     if (input[0] != 'P' || (input[1] != '6' && input[1] != '3')) 
//     {
//         fprintf(stderr, "Invalid PPM file format\n");
//         fclose(file);
//         return NULL;
//     }

//     int32_t col, ligne, max;
//     fscanf(file, "%d %d\n%d\n", &col, &ligne, &max); // Read image dimensions and max value

//     // Allocate memory for imagePGM structure
//     imagePGM* img = (imagePGM*)malloc(sizeof(imagePGM));
//     if (!img) {
//         fclose(file);
//         return NULL;
//     }

//     // Set image dimensions and max value
//     img->col = col;
//     img->ligne = ligne;
//     img->max = max;

//     // Allocate memory for image data
//     img->tab = (Triplet_RGB**)malloc(ligne * sizeof(Triplet_RGB*));
//     if (!img->tab) {
//         fclose(file);
//         free(img);
//         return NULL;
//     }

//     for (int i = 0; i < ligne; i++) {
//         img->tab[i] = (Triplet_RGB*)malloc(col * sizeof(Triplet_RGB));
//         if (!img->tab[i]) {
//             fclose(file);
//             free(img->tab);
//             free(img);
//             return NULL;
//         }
//     }

//     // Read image data
//     for (int i = 0; i < ligne; i++) {
//         for (int j = 0; j < col; j++) {
//             fread(&img->tab[i][j], sizeof(Triplet_RGB), 1, file);
//         }
//     }

//     fclose(file);
//     return img;
// }

imagePGM* recupereimage(char* file){
    imagePGM* image = malloc(sizeof(imagePGM));
    FILE* fichier_PGM = fopen(file, "rb"); //on lit binaire d'où le rb
    if (fichier_PGM == NULL){
        perror("fichier n'existe pas");
        exit(1);
    }
    char premiere_ligne[3];
    bool existe = true;
    existe = fgets(premiere_ligne, sizeof(premiere_ligne), fichier_PGM); // on passe la première ligne avec la version
    existe = fscanf(fichier_PGM, "%hd %hd", &image->col, &image->ligne); //on recupere le nb de colonne et ligne
    existe = fscanf(fichier_PGM, "%hhd", &image->max); // on recupere le niveau max de gris


    image->tab = malloc(sizeof(uint8_t*)*image->ligne); //on va initialiser la matrice
    if (image->tab ==NULL){
        perror("allocation echouée");
        exit(1);
    }
    for (uint32_t i = 0; i < image->ligne; i++){
        image->tab[i] = malloc(sizeof(uint8_t)*image->ligne);
        if (image->tab[i] ==NULL){
            perror("allocation echouée");
            exit(1);
        }
    }
    //fin de l'initialisation de la matrice
    fgetc(fichier_PGM);
    for (uint32_t i = 0; i < image->ligne; i++){
        image->tab[i] = malloc(sizeof(uint8_t) * image->col); // Allocate memory for columns
        if (image->tab[i] == NULL){
            perror("Allocation de mémoire échouée");
            exit(1);
        }
        existe = fread(image->tab[i], sizeof(uint8_t), image->col, fichier_PGM); // Read row data
    }
    fclose(fichier_PGM);
    if(!existe){
        perror("Erreur de lecture du fichier\n");
        return NULL;
    }
    return image;
}

void libere_image(imagePGM* image){
    for (uint32_t i = 0; i < image->ligne; i++){
        free(image->tab[i]);
    }
    free(image->tab);
    free(image);
}
