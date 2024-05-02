#include "MCU.h"

uint32_t entier_superieur(uint32_t l)
{
    return 8 * ((l + 7) / 8);
}

MCU *decoupage(imagePGM *tab)
{
    uint32_t ligne = entier_superieur(tab->ligne);
    uint32_t colonne = entier_superieur(tab->col);
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
    for (i = 0; i < ligne; i += 8)
    {
        for (j = 0; j < colonne; j += 8)
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
                if (courant->tab[k] == NULL)
                {
                    free_decoupage(tete);
                    return NULL;
                }
                for (l = 0; l < 8; l++)
                {
                    if (i + k < tab->ligne && j + l < tab->col)
                    {
                        courant->tab[k][l] = tab2[i + k][j + l];
                    }
                    else
                    {
                        courant->tab[k][l] = 0;
                    }
                }
            }
        }
    }
    return tete;
}   