#include "../include/MCU.h"
#include "../include/recupereimage.h"

uint32_t entier_inferieur(uint32_t l)
{
    return 8 * (l / 8);
}


int min(int a, int b)
{
    if (a < b)
    {
        return a;
    }
    return b;
}

imagePGM *nouveau_tableau(imagePGM *image)
{
    uint32_t nb_ligne = image->ligne;
    uint32_t nb_colonne = image->col;
    uint32_t new_ligne = entier_inferieur(nb_ligne);
    uint32_t new_colonne = entier_inferieur(nb_colonne);

    if (new_ligne != nb_ligne || new_colonne != nb_colonne)
    {
        // ON va créer une imagePGM avec des bords mutiples de 8
        imagePGM *new_tab = malloc(sizeof(imagePGM));

        new_tab->ligne = (new_ligne != nb_ligne) ? new_ligne + 8 : nb_ligne;
        new_tab->col = (new_colonne != nb_colonne) ? new_colonne + 8 : nb_colonne;
        new_tab->max = image->max;

        new_tab->tab = malloc(new_tab->ligne * sizeof(uint8_t *));

        for (uint32_t i = 0; i < new_tab->ligne; i++)
        {
            new_tab->tab[i] = malloc(new_tab->col * sizeof(uint8_t));
            for (uint32_t j = 0; j < new_tab->col; j++)
            {
                uint32_t i0 = min(i, nb_ligne - 1);
                uint32_t j0 = min(j, nb_colonne - 1);
                new_tab->tab[i][j] = image->tab[i0][j0];   
            }
        }
        return new_tab;
    }
    return image;
}

uint8_t **decoupage(imagePGM *tab,uint32_t i,uint32_t j,uint8_t **tableau) //tab aux bonnes dimensions
{
    for (uint8_t k = 0; k < 8; k++)
    {
        for (uint8_t l = 0; l < 8; l++)
        {
            tableau[l][k] = tab -> tab[i + l][j + k];
        }
    }
    return tableau;
}

// void decoupe_1(char* file)
// {
//     imagePGM *img = recupereimage(file);
    
//     for(uint32_t i = 0; i < img->ligne; i++) {
//         for(uint32_t j = 0; j < img->col; j++) {
//             printf("%d \t", img->tab[i][j]);
//         }
//         printf("\n");
//     }
//     printf("\nDécoupe\n");
    
//     MCU *mcu = decoupage(img,0,0);
//     uint32_t i = 0, j = 0;
//     while(mcu != NULL)
//     {
//         for (i = 0; i < 8; i++)
//         {
//             for (j = 0; j < 8; j++)
//             {
//                 printf("%d\t", mcu->tab[i][j]);
//             }
//             printf("\n");
//         }
//         mcu = mcu->suiv;
//     }
// }

// int main(int argc, char *argv[])
// {
//     if (argc < 2)
//     {
//         fprintf(stderr, "Usage: %s <fichier>\n", argv[0]);
//         return 1;
//     }
//     for (int i = 1; i < argc; i++)
//     {
//         printf("Fichier %s\n", argv[i]);
//         decoupe_1(argv[i]);
//         printf("\n");
//     }
    
//     return 0;
// }