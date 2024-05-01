#ifndef _JPEG_FORMAT_H_
#define _JPEG_FORMAT_H_
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


/**
* @brief ecrit la partie generique du debut dans le fichier
* @param file le fichier dans lequel on ecrit le format jpeg
* @return rien hehe
*
**/


void ecrire_debut(char* file);


/**
* @brief ecrit la partie generique de la fin dans le fichier
* @param file le fichier dans lequel on ecrit le format jpeg
* @return rien hehe
*
**/

void ecrire_fin(char* file);


/**
* @brief ecrit la partie pour ecrire les tables quantification
* @param file le fichier dans lequel on ecrit le format jpeg // table_Y la table de quantification de Y // table_CbCr la table de quantification de CbCr
* @return rien hehe
*
**/

void ecrire_qtable( char* file, uint8_t* table_Y, uint8_t* table_CbCr);


/**
* @brief ecrit la partie pour ecrire les tables huffman
* @param file le fichier dans lequel on ecrit le format jpeg // htable_DC_Y la table de huffman de DC de Y // htable_DC_CbCr la table DC huffman de CbCr
* @param htable_nb_length la table de huffman avec le nombre de de symbole de longueur entre 1 et 16
* @return rien hehe
*
**/

void ecrire_htable(char* file, uint8_t* htable_DC_Y, uint8_t* htable_AC_Y, uint8_t* htable_DC_CbCr, uint8_t* htable_AC_CbCr, uint8_t*** htable_nb_length);


#endif
