#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../include/jpeg_format.h"
#include "../include/magnetude_dc.h"
#include "../include/qtables.h"
#include "../include/htables.h"
#include <math.h>


void ecrire_debut(FILE* fptr){
    if (fptr == NULL){
        perror("pas reussi a créer");
    }
    int8_t tab[20] = {0xff,0xd8,0xff, 0xe0, 0x00, 0x10, 0x4a, 0x46, 0x49, 0x46, 0x00,0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00 }; 
    for (int i = 0; i < 20;i++){
        fwrite(&tab[i],sizeof(int8_t),1,fptr);
    }
     
}


void ecrire_fin(FILE* fptr){
    int16_t prefin = 0x80e6;
    int16_t fin = 0xd9ff;
    fwrite(&prefin, sizeof(int16_t), 1, fptr);
    fwrite(&fin, sizeof(int16_t), 1, fptr);
     
}


void ecrire_qtable( FILE* fptr, uint8_t* table_Y, uint8_t* table_CbCr){
    // Indice de table quantification pour Y est 0
    int16_t marqueur = 0xdbff;
    int16_t length = 0x4300;                //la longueur de la section
    int8_t precision = 0x00;
    fwrite(&marqueur, sizeof(int16_t), 1, fptr);
    fwrite(&length, sizeof(int16_t), 1, fptr);
    fwrite(&precision, sizeof(int8_t),1,fptr);
    for (int8_t i = 0; i < 64; i++){
        fwrite(&table_Y[i], sizeof(uint8_t), 1, fptr);
    }
    // int8_t precision1 = 0x01;                   // Indice de table quantification pour CbCr est 1
    // fwrite(&marqueur, sizeof(int16_t), 1, fptr);
    // fwrite(&length, sizeof(int16_t), 1, fptr);
    // fwrite(&precision1, sizeof(int8_t),1,fptr);
    // for (int8_t i = 0; i < 64; i++){
    //     fwrite(&table_CbCr[i], sizeof(uint8_t), 1, fptr);
    // }
     
}


void ecrire_htable(FILE* fptr , uint8_t* htable_DC_Y, uint8_t* htable_AC_Y, uint8_t* htable_DC_CbCr, uint8_t* htable_AC_CbCr, uint8_t htable_nb_length[][3][16]){
    int16_t marqueur = 0xc4ff;  
    int16_t length = 0x1f00;                //la longueur de la section
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


    // int8_t precision2 = 0x01;                //indice 1 , et type 0 car DC pour CbCr
    // fwrite(&marqueur, sizeof(int16_t), 1, fptr);
    // fwrite(&length, sizeof(int16_t), 1, fptr);
    // fwrite(&precision2, sizeof(int8_t),1,fptr);
    // for (int8_t j = 0; j < 16; j++){
    //     fwrite(&htable_nb_length[0][1][j], sizeof(uint8_t), 1, fptr);
    // }
    // for (int8_t i = 0; i < 12; i++){
    //     fwrite(&htable_DC_CbCr[i], sizeof(uint8_t), 1, fptr);
    // }

    int16_t length2 = 0xb500;        
    int8_t precision3 = 0x12;                //indice 2 , et type 1 car AC pour Y
    fwrite(&marqueur, sizeof(int16_t), 1, fptr);
    fwrite(&length2, sizeof(int16_t), 1, fptr);
    fwrite(&precision3, sizeof(int8_t),1,fptr);
    for (int j = 0; j < 16; j++){
        fwrite(&htable_nb_length[1][0][j], sizeof(uint8_t), 1, fptr);
    }
    for (int i = 0; i < 162; i++){
        fwrite(&htable_AC_Y[i], sizeof(uint8_t), 1, fptr);
    }


    // int8_t precision4 = 0x13;                //indice 3 , et type 1 car AC pour CbCr
    // fwrite(&marqueur, sizeof(int16_t), 1, fptr);
    // fwrite(&length2, sizeof(int16_t), 1, fptr);
    // fwrite(&precision4, sizeof(int8_t),1,fptr);
    // for (int8_t j = 0; j < 16; j++){
    //     fwrite(&htable_nb_length[1][1][j], sizeof(uint8_t), 1, fptr);
    // }
    // for (int i = 0; i < 162; i++){
    //     fwrite(&htable_AC_CbCr[i], sizeof(uint8_t), 1, fptr);
    // }
     
}   


void ecrire_SOF(FILE* fptr, uint8_t hauteur_image, uint8_t largeur_image){
    int16_t marqueur = 0xc0ff;
    int16_t length = 0x0b00;                            //la longueur de la section
    int8_t precision = 0x08;     
    int8_t nb_composante = 0x01;   
    int8_t zero = 0x00;                     // nb de composante de 1 pour l'instant car niveaux gris et mettre a 3 si YCbCr               
    fwrite(&marqueur, sizeof(int16_t), 1, fptr);
    fwrite(&length, sizeof(int16_t), 1, fptr);
    fwrite(&precision, sizeof(int8_t),1,fptr);
    fwrite(&zero, sizeof(int8_t), 1, fptr); //on ecrit la hauteur
    fwrite(&hauteur_image, sizeof(int8_t), 1, fptr); //on ecrit la hauteur
    fwrite(&zero, sizeof(int8_t), 1, fptr); //on ecrit la hauteur
    fwrite(&largeur_image, sizeof(int8_t), 1, fptr); // on ecrit la largeur
    fwrite(&nb_composante, sizeof(int8_t),1,fptr);
    int8_t identifiant = 0x00;
    int8_t facteur_echantillonage = 0x11;
    int8_t table_quantification_Y = 0x00;               // indice de table quantification deY est 0 comme vu au dessus
    int8_t table_quantification_CbCr = 0x01;             // indice de table quantification de CbCr est 1 comme vu au dessus
    for (int i = 0; i < nb_composante; i++){         //la première composante sera pour Y et les 2 derniere pur Cb et Cr lorsque nb_composatne = 3
        fwrite(&identifiant, sizeof(int8_t),1,fptr);
        identifiant += 0x01;
        fwrite(&facteur_echantillonage, sizeof(int8_t),1,fptr);        // facteur à 4 car pour l'instant pas de ss-echantillonage

        if (i > 0){
            fwrite(&table_quantification_CbCr, sizeof(int8_t),1,fptr);
        }
        else{
            fwrite(&table_quantification_Y, sizeof(int8_t),1,fptr);
        }
    }
     
}

void ecrire_SOS(FILE* fptr, uint8_t* tab_MCU_huffman_Y, uint16_t nb_MCU_Y)  //,uint8_t*** tab_MCU_huffman_Cb, uint8_t*** tab_MCU_huffman_Cr )
    {
    int16_t marqueur = 0xdaff;
    int16_t length = 0x0800;                            //la longueur de la section vaut 2* nb_composante + 6 ici nb_composante = 1 car niveaux gris   
    int8_t nb_composante = 0x01;  
    fwrite(&marqueur, sizeof(int16_t), 1, fptr);
    fwrite(&length, sizeof(int16_t), 1, fptr);
    fwrite(&nb_composante, sizeof(int8_t),1,fptr);
    int8_t identifiant = 0x00;
    int8_t indice_huffman_Y = 0x02;                     // 4 premier bits pour indice table DC et 4 bits pour table AC
    int8_t indice_huffman_CbCr = 0x13;                     // 4 premier bits pour indice table DC et 4 bits pour table AC
    for (int i = 0; i < nb_composante; i++){       //la première composante sera pour Y et les 2 derniere pur Cb et Cr lorsque nb_composatne = 3 
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
    // for (uint16_t i = 0; i < nb_MCU_Y; i ++){
    uint16_t i =0;
    int8_t biffleur = 7;
    uint8_t nb = 0;
    while (tab_MCU_huffman_Y[i] != 88 ){
        if (biffleur==-1){ // on écrit 
            biffleur = 7;
            fwrite(&nb, sizeof(uint8_t),1,fptr);
            nb = 0;
        }
        else{
            nb = nb + pow(2,biffleur)*tab_MCU_huffman_Y[i];
            i ++;
            biffleur--;
        }        
    }
    // }
    }



// int main(){
//     char* filename = "test_image.jpeg";
//     FILE* fptr = fopen(filename, "wb");
//     ecrire_debut(fptr);
//     ecrire_SOF(fptr,8,8);
//     ecrire_qtable(fptr, quantification_table_Y, quantification_table_CbCr);
//     ecrire_htable(fptr,htables_symbols[0][0],htables_symbols[1][0],htables_symbols[0][1],htables_symbols[1][1],htables_nb_symb_per_lengths);
//     ecrire_fin(fptr);
//     fclose(fptr);
//     return 0;
// }