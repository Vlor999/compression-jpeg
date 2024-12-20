#ifndef _JPEG_FORMAT_H_
#define _JPEG_FORMAT_H_
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>


struct ecritureSOS{
    int8_t compteur;
    uint8_t nb;
};
typedef struct ecritureSOS ecritureSOS;

/**
* @brief ecrit la partie generique du debut dans le fichier
* @param file le fichier dans lequel on ecrit le format jpeg
* @return rien hehe
*
**/
void ecrire_debut(FILE* fptr);


/**
* @brief ecrit la partie generique de la fin dans le fichier
* @param file le fichier dans lequel on ecrit le format jpeg
* @return rien hehe
*
**/
void ecrire_fin(FILE* fptr);


/**
* @brief ecrit la partie pour ecrire les tables quantification
* @param file le fichier dans lequel on ecrit le format jpeg // table_Y la table de quantification de Y // table_CbCr la table de quantification de CbCr
* @return rien hehe
*
**/
void ecrire_qtable( FILE* fptr, bool couleur);


/**
* @brief ecrit la partie pour ecrire les tables huffman
* @param file le fichier dans lequel on ecrit le format jpeg // htable_DC_Y la table de huffman de DC de Y // htable_DC_CbCr la table DC huffman de CbCr
* @param htable_nb_length la table de huffman avec le nombre de de symbole de longueur entre 1 et 16
* @return rien hehe
*
**/
// FILE* fptr, uint8_t* htable_DC_Y, uint8_t* htable_AC_Y, uint8_t* htable_DC_CbCr, uint8_t* htable_AC_CbCr, uint8_t htable_nb_length[][3][16],bool couleur
void ecrire_htable(FILE* fptr,uint8_t htable_nb_length[][3][16], bool couleur);



/**
* @brief ecrit la partie SOF pour donner les specifications sur l'image
* @param file le fichier dans lequel on ecrit le format jpeg // hauteur de l'imgae // largeur de l'image // facteurs qui sont les facteurs d'echantillonnages peut valoir NULL si onp rend facteurs par defaut
* @return rien hehe
*
**/
void ecrire_SOF(FILE* fptr, uint16_t hauteur_image, uint16_t largeur_image,uint8_t* facteurs,bool couleur);




/**
* @brief ecrit la partie SOS l'en tete
* @param file le fichier dans lequel on ecrit le format jpeg // tab_MCU_Huffman_Y tableau contenant nb_MCU et 
*        chaque valeur est un tableau de MCU (donc 8x8 =64) et dans les MCU les 64 valeurs sont les codes de huffman sous forme de tableau
         nb_MCU_Y correspond a len(tab_MCU_Huffman_Y)
* @return rien hehe
**/
void ecrire_SOS_en_tete(FILE* fptr, bool couleur);


/**
* @brief ecrit la partie SOS le contenue
* @param file le fichier dans lequel on ecrit le format jpeg // tab_MCU_Huffman_Y tableau contenant nb_MCU et 
*        chaque valeur est un tableau de MCU (donc 8x8 =64) et dans les MCU les 64 valeurs sont les codes de huffman sous forme de tableau
         nb_MCU_Y correspond a len(tab_MCU_Huffman_Y)
* @return rien hehe
**/
ecritureSOS *ecrire_SOS_contenu(FILE* fptr, uint8_t* tab_MCU_huffman_Y,ecritureSOS *ecr);
    // ecriture par bloc de 8x8 par nb de bloc et par ordre de composante


/**
 * @brief On ecrit un commentaire à la fin des MCU pour préciser la fin
 * @param fptr le fichier dans lequel on écrit
 * @return rien
 **/
uint8_t reverse_hexa(uint8_t valeur);
void ecrire_commentaire_SOS(FILE* fptr);

void ecrire_commentaire_SOS_PC(FILE* fptr);

void ecriture_en_tete(FILE* fptr, uint32_t nombre_ligne, uint16_t nombre_colonne, uint8_t* tableau, bool couleur);


#endif
