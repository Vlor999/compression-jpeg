// #include <time.h>
// #include <stdio.h>
// #include <stdint.h>
// #include <string.h>

// int main()
// {
//     char* titre = "titre_akjd.jpg";
//     char* sample = "_1x1,1x3,1x2.jpg";
//     uint16_t taille = strlen(titre);
//     printf("Taille du titre : %d\n", taille);
//     char titre2[taille + 13];
//     for(uint16_t i = 0; i < taille - 4; i++)
//     {
//         titre2[i] = titre[i];
//     }
//     for(uint8_t i = 0; i < 16; i++ )
//     {
//         titre2[i + taille - 4] = sample[i];
//     }

//     printf("Titre2 : %s\n", titre2);
// }