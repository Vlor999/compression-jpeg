#include "../include/MCU.h"
#include "../include/recupereimage.h"

uint32_t entier_inferieur(uint32_t l)
{
    return 8 * (l / 8);
}

void free_decoupage(MCU *m)
{
    if (m == NULL)
    {
        return;
    }
    for (int i = 0; i < 8; i++)
    {
        free(m->tab[i]);
    }
    free(m->tab);
    free_decoupage(m->suiv);
    free(m);
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

MCU *decoupage(imagePGM *tab)
{
    tab = nouveau_tableau(tab);
    // On a une image avec des bords multiples de 8

    uint32_t i, j, k, l;
    uint8_t **tab2 = tab->tab;
    MCU *tete = malloc(sizeof(MCU));
    if (tete == NULL)
    {
        return NULL;
    }
    tete->tab = malloc(8 * sizeof(uint8_t *));
    if (tete->tab == NULL)
    {
        free(tete);
        return NULL;
    }
    tete->ligne = 0;
    tete->colonne = 0;
    tete->suiv = NULL;
    for (i = 0; i < 8; i++)
    {
        tete->tab[i] = malloc(8 * sizeof(uint8_t));
        if (tete->tab[i] == NULL)
        {
            free_decoupage(tete);
            return NULL;
        }
        for (j = 0; j < 8; j++)
        {
            tete->tab[i][j] = tab2[i][j];
        }
    }
    MCU *courant = tete;
    for (i = 0; i < tab->ligne; i += 8)
    {
        for (j = 0; j < tab->col; j += 8)
        {
            if (i == 0 && j == 0)
            {
                continue;
            }
            courant->suiv = malloc(sizeof(MCU));
            if (courant->suiv == NULL)
            {
                free_decoupage(tete);
                return NULL;
            }
            courant = courant->suiv;
            courant->tab = malloc(8 * sizeof(uint8_t *));
            if (courant->tab == NULL)
            {
                free_decoupage(tete);
                return NULL;
            }
            courant->ligne = i;
            courant->colonne = j;
            courant->suiv = NULL;
            for (k = 0; k < 8; k++)
            {
                courant->tab[k] = malloc(8 * sizeof(uint8_t));
            }
            for (k = 0; k < 8; k++)
            {
                if (courant->tab[k] == NULL)
                {
                    free_decoupage(tete);
                    return NULL;
                }
                for (l = 0; l < 8; l++)
                {
                    courant->tab[l][k] = tab2[j + l][i + k];
                }
            }
        }
    }
    return tete;
}

void decoupe_1(char* file)
{
    imagePGM *img = recupereimage(file);
    
    for(uint32_t i = 0; i < img->ligne; i++) {
        for(uint32_t j = 0; j < img->col; j++) {
            printf("%d \t", img->tab[i][j]);
        }
        printf("\n");
    }
    printf("\nDécoupe\n");
    
    MCU *mcu = decoupage(img);
    uint32_t i = 0, j = 0;
    while(mcu != NULL)
    {
        for (i = 0; i < 8; i++)
        {
            for (j = 0; j < 8; j++)
            {
                printf("%d\t", mcu->tab[i][j]);
            }
            printf("\n");
        }
        mcu = mcu->suiv;
    }
}

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