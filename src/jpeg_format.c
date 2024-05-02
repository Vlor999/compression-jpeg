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
    int8_t precision = 0x00;                //indice 0 , et type 0 car DC pour Y
    fwrite(&marqueur, sizeof(int16_t), 1, fptr);
    fwrite(&length, sizeof(int16_t), 1, fptr);
    fwrite(&precision, sizeof(int8_t),1,fptr);
    for (int8_t j = 0; j < 16; j++){
        fwrite(&htable_nb_length[0][0][j], sizeof(uint8_t), 1, fptr);
    }
    for (int8_t i = 0; i < 12; i++){
        fwrite(&htable_DC_Y[i], sizeof(uint8_t), 1, fptr);
    }


    int8_t precision = 0x01;                //indice 1 , et type 0 car DC pour CbCr
    fwrite(&marqueur, sizeof(int16_t), 1, fptr);
    fwrite(&length, sizeof(int16_t), 1, fptr);
    fwrite(&precision, sizeof(int8_t),1,fptr);
    for (int8_t j = 0; j < 16; j++){
        fwrite(&htable_nb_length[0][1][j], sizeof(uint8_t), 1, fptr);
    }
    for (int8_t i = 0; i < 12; i++){
        fwrite(&htable_DC_CbCr[i], sizeof(uint8_t), 1, fptr);
    }


    int8_t precision = 0x12;                //indice 2 , et type 1 car AC pour Y
    fwrite(&marqueur, sizeof(int16_t), 1, fptr);
    fwrite(&length, sizeof(int16_t), 1, fptr);
    fwrite(&precision, sizeof(int8_t),1,fptr);
    for (int8_t j = 0; j < 16; j++){
        fwrite(&htable_nb_length[1][0][j], sizeof(uint8_t), 1, fptr);
    }
    for (int8_t i = 0; i < 162; i++){
        fwrite(&htable_AC_Y[i], sizeof(uint8_t), 1, fptr);
    }


    int8_t precision = 0x13;                //indice 3 , et type 1 car AC pour CbCr
    fwrite(&marqueur, sizeof(int16_t), 1, fptr);
    fwrite(&length, sizeof(int16_t), 1, fptr);
    fwrite(&precision, sizeof(int8_t),1,fptr);
    for (int8_t j = 0; j < 16; j++){
        fwrite(&htable_nb_length[1][1][j], sizeof(uint8_t), 1, fptr);
    }
    for (int8_t i = 0; i < 162; i++){
        fwrite(&htable_AC_CbCr[i], sizeof(uint8_t), 1, fptr);
    }
    fclose(file);
}   


void ecrire_SOF(char* file, uint16_t hauteur_image, uint16_t largeur_image){
    FILE* fptr = fopen(file, "wb");
    int16_t marqueur = 0xffc0;
    int16_t length = 0x000b;                            //la longueur de la section
    int8_t precision = 0x08;     
    int8_t nb_composante = 0x01;                        // nb de composante de 1 pour l'instant car niveaux gris et mettre a 3 si YCbCr               
    fwrite(&marqueur, sizeof(int16_t), 1, fptr);
    fwrite(&length, sizeof(int16_t), 1, fptr);
    fwrite(&precision, sizeof(int8_t),1,fptr);
    fwrite(&hauteur_image, sizeof(int16_t), 1, fptr); //on ecrit la hauteur
    fwrite(&largeur_image, sizeof(int16_t), 1, fptr); // on ecrit la largeur
    fwrite(&nb_composante, sizeof(int8_t),1,fptr);
    int8_t identifiant = 0x00;
    int8_t facteur_echantillonage = 0x01;
    int8_t table_quantification_Y = 0x00;               // indice de table quantification deY est 0 comme vu au dessus
    int8_t table_quantification_CbCr = 0x01;             // indice de table quantification de CbCr est 1 comme vu au dessus
    for (int8_t i = 0; i < nb_composante; i++){         //la première composante sera pour Y et les 2 derniere pur Cb et Cr lorsque nb_composatne = 3
        fwrite(&identifiant, sizeof(int8_t),1,fptr);
        identifiant += 0x01;
        fwrite(&facteur_echantillonage, sizeof(int8_t),1,fptr);        // facteur à 4 car pour l'instant pas de ss-echantillonage
        fwrite(&facteur_echantillonage, sizeof(int8_t),1,fptr);       // facteur à 4 car pour l'instant pas de ss-echantillonage
        if (i > 0){
            fwrite(&table_quantification_CbCr, sizeof(int8_t),1,fptr);
        }
        else{
            fwrite(&table_quantification_Y, sizeof(int8_t),1,fptr);
        }
    }
    fclose(file);
}

void ecrire_SOS(char* file, uint8_t*** tab_MCU_huffman_Y, uint16_t nb_MCU_Y)  //,uint8_t*** tab_MCU_huffman_Cb, uint8_t*** tab_MCU_huffman_Cr )
    {
    FILE* fptr = fopen(file, "wb");
    int16_t marqueur = 0xffda;
    int16_t length = 0x0008;                            //la longueur de la section vaut 2* nb_composante + 6 ici nb_composante = 1 car niveaux gris   
    int8_t nb_composante = 0x01;  
    fwrite(&marqueur, sizeof(int16_t), 1, fptr);
    fwrite(&length, sizeof(int16_t), 1, fptr);
    fwrite(&nb_composante, sizeof(int8_t),1,fptr);
    int8_t identifiant = 0x00;
    int8_t indice_huffman_Y = 0x02;                     // 4 premier bits pour indice table DC et 4 bits pour table AC
    int8_t indice_huffman_CbCr = 0x13;                     // 4 premier bits pour indice table DC et 4 bits pour table AC
    for (int8_t i = 0; i < nb_composante; i++){       //la première composante sera pour Y et les 2 derniere pur Cb et Cr lorsque nb_composatne = 3 
        fwrite(&identifiant, sizeof(int8_t),1,fptr);
        identifiant += 0x01;
        if (i > 0){
            fwrite(&indice_huffman_CbCr, sizeof(int8_t),1,fptr);
        }
        else{
            fwrite(&indice_huffman_Y, sizeof(int8_t),1,fptr);
        }
        }

    // juste par convention la suite
    int8_t val_zero = 0x00;
    int8_t val_se = 0x3f;
    fwrite(&val_zero, sizeof(int8_t),1,fptr);
    fwrite(&val_se, sizeof(int8_t),1,fptr);
    fwrite(&val_zero, sizeof(int8_t),1,fptr);

    // ecriture par bloc de 8x8 par nb de bloc et par ordre de composante

    for (uint16_t i = 0; i < nb_MCU_Y; i ++){
        for (uint8_t j = 0; j <64; j ++){
            fwrite(&tab_MCU_huffman_Y[i][j][0], sizeof(uint8_t),1,fptr);
            fwrite(&tab_MCU_huffman_Y[i][j][1], sizeof(uint8_t),1,fptr);
        }
    }


    fclose(file);
    }
