#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "jpeg_format.h"


void ecrire_debut(char* file){
    FILE* fptr = fopen(file, 'wb');
    if (fptr == NULL){
        perror("pas reussi a créer");
    }
    int8_t* tab = { 0xff, 0xd8,0xff,0xd9,0xff, 0xe0, 0x00, 0x10, 0x4a, 0x46, 0x49, 0x46, 0x00,0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; 
    for (int i = 0; i < 22;i++){
        fwrite(&tab[i],sizeof(int8_t),1,fptr);
    }
    fclose(file);
}


void ecrire_fin(char* file){
    FILE* fptr = fopen(file,'wb');
    int16_t fin = 0xffd9;
    fwrite(&fin, sizeof(int16_t), 1, fptr);
    fclose(file);
}


void ecrire_qtable( char* file, uint8_t* table_Y, uint8_t* table_CbCr){
    FILE* fptr = fopen(file, "wb");                // Indice de table quantification pour Y est 0
    int16_t marqueur = 0xffdb;
    int16_t length = 0x0043;                //la longueur de la section
    int8_t precision = 0x00;
    fwrite(&marqueur, sizeof(int16_t), 1, fptr);
    fwrite(&length, sizeof(int16_t), 1, fptr);
    fwrite(&precision, sizeof(int8_t),1,fptr);
    for (int8_t i = 0; i < 64; i++){
        fwrite(&table_Y[i], sizeof(uint8_t), 1, fptr);
    }
    int8_t precision1 = 0x01;                   // Indice de table quantification pour CbCr est 1
    fwrite(&marqueur, sizeof(int16_t), 1, fptr);
    fwrite(&length, sizeof(int16_t), 1, fptr);
    fwrite(&precision1, sizeof(int8_t),1,fptr);
    for (int8_t i = 0; i < 64; i++){
        fwrite(&table_CbCr[i], sizeof(uint8_t), 1, fptr);
    }
    fclose(file);
}


void ecrire_htable(char* file, uint8_t* htable_DC_Y, uint8_t* htable_AC_Y, uint8_t* htable_DC_CbCr, uint8_t* htable_AC_CbCr, uint8_t*** htable_nb_length){
    FILE* fptr = fopen(file, "wb");
    int16_t marqueur = 0xffc4;  
    int16_t length = 0x0015;                //la longueur de la section
    int8_t precision = 0x00;                //indice 0 , et type 0 car DC
    fwrite(&marqueur, sizeof(int16_t), 1, fptr);
    fwrite(&length, sizeof(int16_t), 1, fptr);
    fwrite(&precision, sizeof(int8_t),1,fptr);
    for (int8_t j = 0; j < 16; j++){
        fwrite(&htable_nb_length[0][0][j], sizeof(uint8_t), 1, fptr);
    }
    for (int8_t i = 0; i < 12; i++){
        fwrite(&htable_DC_Y[i], sizeof(uint8_t), 1, fptr);
    }


    int8_t precision = 0x01;                //indice 1 , et type 0 car DC
    fwrite(&marqueur, sizeof(int16_t), 1, fptr);
    fwrite(&length, sizeof(int16_t), 1, fptr);
    fwrite(&precision, sizeof(int8_t),1,fptr);
    for (int8_t j = 0; j < 16; j++){
        fwrite(&htable_nb_length[0][1][j], sizeof(uint8_t), 1, fptr);
    }
    for (int8_t i = 0; i < 12; i++){
        fwrite(&htable_DC_CbCr[i], sizeof(uint8_t), 1, fptr);
    }


    int8_t precision = 0x12;                //indice 2 , et type 1 car AC
    fwrite(&marqueur, sizeof(int16_t), 1, fptr);
    fwrite(&length, sizeof(int16_t), 1, fptr);
    fwrite(&precision, sizeof(int8_t),1,fptr);
    for (int8_t j = 0; j < 16; j++){
        fwrite(&htable_nb_length[1][0][j], sizeof(uint8_t), 1, fptr);
    }
    for (int8_t i = 0; i < 162; i++){
        fwrite(&htable_AC_Y[i], sizeof(uint8_t), 1, fptr);
    }


    int8_t precision = 0x13;                //indice 3 , et type 1 car AC
    fwrite(&marqueur, sizeof(int16_t), 1, fptr);
    fwrite(&length, sizeof(int16_t), 1, fptr);
    fwrite(&precision, sizeof(int8_t),1,fptr);
    for (int8_t j = 0; j < 16; j++){
        fwrite(&htable_nb_length[1][1][j], sizeof(uint8_t), 1, fptr);
    }
    for (int8_t i = 0; i < 162; i++){
        fwrite(&htable_AC_CbCr[i], sizeof(uint8_t), 1, fptr);
    }

}


void ecrire_SOF(char* file, uint16_t hauteur_image, uint16_t largeur_image){
    FILE* fptr = fopen(file, "wb");
    int16_t marqueur = 0xffc0;
    int16_t length = 0x000b;                            //la longueur de la section
    int8_t precision = 0x08;                    
    fwrite(&marqueur, sizeof(int16_t), 1, fptr);
    fwrite(&length, sizeof(int16_t), 1, fptr);
    fwrite(&precision, sizeof(int8_t),1,fptr);
    fwrite(&hauteur_image, sizeof(int16_t), 1, fptr); //on ecrit la hauteur
    fwrite(&largeur_image, sizeof(int16_t), 1, fptr); // on ecrit la largeur

}

