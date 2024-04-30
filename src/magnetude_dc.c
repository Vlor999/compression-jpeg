//#include "../include/htables.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

uint8_t trouver_magnetude(uint32_t n){
    int64_t nombre=1;
    for (uint8_t k=0;k<12;k++){
        if (nombre-1 >= n && -(nombre-1) <= n){
            return k;
        }
        nombre = nombre * 2;
    }
    perror("C'est trop grand chacal t'abuses \n");
}



// int main(){
//     printf("%d\n",trouver_magnetude(77));
//     printf("%d\n",trouver_magnetude(0));
//     printf("%d\n",trouver_magnetude(1));
//     printf("%d\n",trouver_magnetude(-150));
//     printf("%d\n",trouver_magnetude(2000));
//     printf("%d\n",trouver_magnetude(-2000));
//     printf("%d\n",trouver_magnetude(14154511));
// }

uint8_t* codage_AC_RLE(uint16_t* tab){  
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


int main(){
    uint16_t tab[64] = {-1,0x0001,0x0000,0x0000,0x0000,0x0001,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000};
    uint8_t* tab_rle = codage_AC_RLE(&tab);
    for (int i = 0 ; i < tab_rle[0]; i++){
        printf("%02x ", tab_rle[i]);
    }
    printf("\n");
    printf("%u",trouver_magnetude(-1));
}
