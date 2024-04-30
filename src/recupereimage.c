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
    fscanf(fichier_PGM, "%d %d", &image->ligne,&image->col); //on recupere le nb de colonne et ligne
    fscanf(fichier_PGM, "%d", &image->max); // on recupere le niveau max de gris

    image->tab = malloc(sizeof(uint8_t*)*image->col); //on va initialiser la matrice
    if (image->tab ==NULL){
        perror("allocation echouée");
        exit(1);
    }
    for (int32_t i = 0; i < image->col; i++){
        image->tab[i] = malloc(sizeof(uint8_t)*image->ligne);
        if (image->tab[i] ==NULL){
            perror("allocation echouée");
            exit(1);
        }
    }
    //fin de l'initialisation de la matrice
    fgetc(fichier_PGM);
    for (int32_t i = 0; i < image->ligne; i++){
        fread(image->tab[i],sizeof(uint8_t), image->ligne, fichier_PGM); // on rcrit valeur binaire dans tableau
    }
    fclose(fichier_PGM);
    return image;
}


// int main(){
//     imagePGM* image = recupereimage("src/our_images/alea_image1.pgm");
//     for (int i= 0; i < image->ligne; i++){
//         for (int j = 0; j < image->col; j ++){
//             printf("%d ", image->tab[i][j]);   
//         }
//         printf("\n");
//     }
//     return 0;
// }