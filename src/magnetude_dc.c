//#include "../include/htables.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

uint8_t trouver_magnetude(int32_t n){
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