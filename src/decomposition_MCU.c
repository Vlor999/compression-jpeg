#include "../include/MCU.h"
#include "../include/recupereimage.h"
#include "../include/conversionRGB.h"

uint32_t entier_inferieur(uint32_t l)
{
    return MCU_TAILLE * (l / MCU_TAILLE);
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

        new_tab->ligne = (new_ligne != nb_ligne) ? new_ligne + MCU_TAILLE : nb_ligne;
        new_tab->col = (new_colonne != nb_colonne) ? new_colonne + MCU_TAILLE : nb_colonne;
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

uint8_t **decoupage(imagePGM *tab, uint32_t i, uint32_t j) //tab aux bonnes dimensions
{
    uint8_t **tableau = malloc(MCU_TAILLE * sizeof(uint8_t*));
    for (uint8_t h = 0; h < MCU_TAILLE; h++)
    {
        tableau[h] = malloc(MCU_TAILLE * sizeof(uint8_t));
    }
    for (uint8_t k = 0; k < MCU_TAILLE; k++)
    {
        for (uint8_t l = 0; l < MCU_TAILLE; l++)
        {
            tableau[l][k] = tab -> tab[i + l][j + k];
        }
    }
    return tableau;
}

uint8_t*** allocation(uint8_t h1, uint8_t v1)
{
    uint8_t ***liste_MCU = malloc((3 * h1 * v1) * sizeof(uint8_t**));
    for (uint8_t k = 0; k < h1 * v1 * 3; k++)
    {
        liste_MCU[k] = malloc(MCU_TAILLE * sizeof(uint8_t*));
        for (uint8_t l = 0; l < MCU_TAILLE; l++)
        {
            liste_MCU[k][l] = malloc(MCU_TAILLE * sizeof(uint8_t));
        }
    }
    return liste_MCU;
}

void liberation(uint8_t*** liste, uint8_t h1, uint8_t v1)
{
    for (uint8_t k = 0; k < h1 * v1 * 3; k++)
    {
        for (uint8_t l = 0; l < MCU_TAILLE; l++)
        {
            free(liste[k][l]);
        }
        free(liste[k]);
    }
    free(liste);
}
