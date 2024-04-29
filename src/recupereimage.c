#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "recupereimage.h"



/**
 * @brief recupere l'image au format pgm 
 *
 * @param file nom du fichier pgm
 * @param image type imagePGM dans lequel on va ecrire les valeurs contenus dans le fichier pgm
 * @return image de type imagePGM
 */


imagePGM* recupereimage(char* file){
    imagePGM* image;
    FILE* fichier_PGM = fopen(file, "rb"); //on lit binaire d'où le rb
    if (fichier_PGM ==NULL){
        perror("fichier n'existe pas");
        exit(1);
    }
    char premiere_ligne[3];
    fgets(premiere_ligne, sizeof(premiere_ligne), fichier_PGM); // on passe la première ligne avec la version
    fscanf(fichier_PGM, "%d %d", &image->col,&image->ligne); //on recupere le nb de colonne et ligne
    fscanf(fichier_PGM, "%d", &image->max); // on recupere le niveau max de gris

    image->tab = malloc(sizeof(uint8_t*)*image->ligne); //on va initialiser la matrice
    if (image->tab ==NULL){
        perror("allocation echoué");
        exit(1);
    }
    for (int32_t i = 0; i < image->ligne; i++){
        image->tab[i] = malloc(sizeof(uint8_t)*image->col);
        if (image->tab[i] ==NULL){
            perror("allocation echoué");
            exit(1);
        }
    }
    //fin de l'initialisation de la matrice

    for (int32_t i = 0; i < image->ligne; i++){
        fread(image->tab[i],sizeof(uint8_t), image->col, fichier_PGM); // on rcrit valeur binaire dans tableau
    }
    fclose(fichier_PGM);
    return image;
}
