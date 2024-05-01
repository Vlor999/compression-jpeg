//#include "../include/htables.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>



uint8_t trouver_magnetude(int16_t n){
    int64_t nombre=1;
    uint16_t n2; //on prend la valeur absolue sinon LES PROBLEMES 
    if (n<0){
        n2=-n;
    }
    else{
        n2=n;
    }
    for (uint8_t k=0;k<12;k++){
        if (nombre-1 >= n2){
            return k;
        }
        nombre = nombre * 2;
    }
    perror("C'est trop grand chacal t'abuses \n");
    return 0;
}


uint8_t* codage_AC_RLE(int16_t* tab){  
    uint8_t* tab_RLE = malloc(sizeof(uint8_t)*64);
    uint8_t indice = 1;
    uint8_t nb_zero = 0;
    for (uint8_t i = 0; i<64; i++){
        if (tab[i] == 0){
            nb_zero ++;
        }
        else{
            uint8_t magnetude = trouver_magnetude(tab[i]);
            tab_RLE[indice] = nb_zero*(16) + magnetude;
            indice ++;
            nb_zero = 0;
        }
    }
    tab_RLE[indice] = 0;
    tab_RLE[0] = indice +1; // l'indice 0 est la taille du tableau qui suit
    tab_RLE = realloc(tab_RLE, sizeof(uint8_t)*(indice +2));
    return tab_RLE;
}


uint8_t *codage_dc_tete(int16_t n){
    
    uint8_t magn = trouver_magnetude(n);
    int64_t nombre = 1;
    uint64_t res;
    int64_t tmp;
    uint8_t *tab;
    for (uint8_t k = 0;k<magn;k++){
        nombre = nombre * 2;   
    }
    nombre = nombre - 1;
    if (n==0){
        tab = malloc(sizeof(uint8_t));
        tab[0]=0; 
    }
    else if (n<0){
        res = (nombre + n) ;
    }
    else{
        tmp = ((int64_t) ((nombre+1) / 2));
        res = (nombre - tmp + 1) + (n - tmp); //les négatifs puis les positifs, on compte tous ceux qui sont avant
    }
    //on transforme res en binaire
    // on a magn qui nous dit sur combien de bits on code res  
    tab = malloc(magn*sizeof(uint8_t));
    for (uint8_t i=0;i<magn;i++){
        tab[magn-i-1]= res%2;
        res = res/2;
    }
    // for (uint8_t i=0;i<magn;i++){
    //     printf("%d ",tab[i]);
    // }
    return tab;
}


// int main(){
//     int16_t tab[64] = {-1,0x0001,0x0000,0x0000,0x0000,0x0001,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000};
//     uint8_t* tab_rle = codage_AC_RLE(&tab);
//     for (int i = 0 ; i < tab_rle[0]; i++){
//         printf("%02x ", tab_rle[i]);
//     }
//     printf("\n");

//     printf("%d\n",trouver_magnetude(-1));
//     uint8_t *t = codage_dc_tete(-23);
//     return 0;
// }
