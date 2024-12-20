#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "../include/conversionRGB.h"
#include "../include/recup_v2.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"

data_frame Lecture_Init(const char *filename)
{
    FILE *file = fopen(filename, "rb");

    if (file == NULL)
    {
        fprintf(stderr, "Erreur d'ouverture: %s\n", filename);
        data_frame data = {0, 0, 0, 0, 0, false, file};
        return data;
    }

    char input[3];
    fscanf(file, "%2s\n", input);
    if (input[0] != 'P' || (input[1] != '6' && input[1] != '5'))
    {
        fprintf(stderr, "Le fromat n'est ni PGM ni PPM\n");
        fclose(file);
        data_frame data = {0, 0, 0, 0, 0, false, file};
        return data;
    }

    uint16_t col, ligne, max;
    uint8_t header = 9;
    bool isRGB = input[1] == '6';
    uint32_t nb_MCU = 0;
    fscanf(file, "%hd %hd\n%hd\n", &col, &ligne, &max);
    

    header = header + (uint8_t)log10(max) + (uint8_t)log10(col) + (uint8_t)log10(ligne);
    nb_MCU = ((col + 7) / MCU_TAILLE) * MCU_TAILLE * ((ligne + 7) / MCU_TAILLE) * MCU_TAILLE / (MCU_TAILLE * MCU_TAILLE);

    data_frame data = {col, ligne, nb_MCU, max, header, isRGB, file};
    return data;
}

MCU_RGB *Read_File(data_frame data, uint64_t number)
{
    /*
    Correction à effectuer :
    - Il y a un porblème si le fichier n'est pas de taille divisible par 8
    - Je ne retrourne aps bien à la ligne et donc cela créer un décalage à chaque fois
    - Quelques effets de bords à voir
    */
    FILE *file = data.file;
    uint32_t nb_colonne = data.nb_colonne;
    uint32_t nb_ligne = data.nb_ligne;

    nb_colonne = ((nb_colonne + MCU_TAILLE - 1) / MCU_TAILLE) * MCU_TAILLE;
    nb_ligne = ((nb_ligne + MCU_TAILLE - 1) / MCU_TAILLE) * MCU_TAILLE;

    uint32_t sous_matrice_par_ligne = nb_colonne / MCU_TAILLE;
    uint32_t debut_ligne = (number / sous_matrice_par_ligne) * MCU_TAILLE;
    uint32_t debut_colonne = (number % sous_matrice_par_ligne) * MCU_TAILLE;

    bool ligne_ok = debut_ligne + MCU_TAILLE <= data.nb_ligne;
    bool colonne_ok = debut_colonne + MCU_TAILLE <= data.nb_colonne;

    uint8_t max_value_i = MCU_TAILLE;
    uint8_t max_value_j = MCU_TAILLE;

    if (!ligne_ok)
    {
        max_value_i = data.nb_ligne - debut_ligne;
    }
    if (!colonne_ok)
    {
        max_value_j = data.nb_colonne - debut_colonne;
    }

    MCU_RGB *mcu = calloc(1, sizeof(MCU_RGB));
    uint8_t taille = sizeof(Triplet_RGB);
    if (!data.isRGB)
    {
        taille = sizeof(uint8_t);
    }

    long int position_debut = data.header * sizeof(uint8_t) + debut_ligne * data.nb_colonne * sizeof(uint8_t) * taille + debut_colonne * sizeof(uint8_t) * taille;
    fseek(file, position_debut, SEEK_SET);

    for (uint8_t i = 0; i < MCU_TAILLE; i++)
    {
        for (uint8_t j = 0; j < MCU_TAILLE; j++)
        {
            if (data.isRGB)
            {
                if (i < max_value_i && j < max_value_j)
                {
                    fread(&mcu->tab[i][j], taille, 1, file);
                }
                else
                {
                    if (j >= max_value_j)
                    {
                        mcu->tab[i][j] = mcu->tab[i][max_value_j - 1];
                    }
                    if (i >= max_value_i)
                    {
                        mcu->tab[i][j] = mcu->tab[max_value_i - 1][j];
                    }
                }
            }
            else
            {
                uint8_t pixel = 0;
                if (i < max_value_i && j < max_value_j)
                {
                    fread(&pixel, taille, 1, file);
                }
                else
                {
                    if (j >= max_value_j)
                    {
                        pixel = mcu->tab[i][max_value_j - 1].R;
                    }
                    if (i >= max_value_i)
                    {
                        pixel = mcu->tab[max_value_i - 1][j].R;
                    }
                }
                mcu->tab[i][j].R = pixel;
                mcu->tab[i][j].G = pixel;
                mcu->tab[i][j].B = pixel;
            }
        }
        fseek(file, (data.nb_colonne - max_value_j) * taille, SEEK_CUR);
    }
    return mcu;
}

void Fermeture_fichier(data_frame data)
{
    fclose(data.file);
}

imagePGM_RGB *LecturePPM(const char *filename)
{
    FILE *file = fopen(filename, "rb");

    if (file == NULL)
    {
        fprintf(stderr, "Erreur d'ouverture: %s\n", filename);
        return NULL;
    }

    char input[3];
    fscanf(file, "%2s\n", input);
    
    if (input[0] != 'P' || (input[1] != '6' && input[1] != '5'))
    {
        fprintf(stderr, "Invalid PPM file format\n");
        fclose(file);
        return NULL;
    }

    int32_t col, ligne, max;
    fscanf(file, "%d %d\n%d\n", &col, &ligne, &max);
    
    imagePGM_RGB *img = malloc(sizeof(imagePGM_RGB));
    if (img == NULL)
    {
        fclose(file);
        return NULL;
    }

    bool isRGB = input[1] == '6';

    img->col = col;
    img->ligne = ligne;
    img->max = max;

    img->tab = (Triplet_RGB **)malloc(ligne * sizeof(Triplet_RGB *));

    for (int32_t i = 0; i < ligne; i++)
    {
        img->tab[i] = malloc(col * sizeof(Triplet_RGB));
        for (int32_t j = 0; j < col; j++)
        {
            if (isRGB)
            {
                fread(&img->tab[i][j], sizeof(Triplet_RGB), 1, file);
            }
            else
            {
                uint8_t *pixel = malloc(sizeof(uint8_t));
                fread(pixel, sizeof(uint8_t), 1, file);
                img->tab[i][j].R = *pixel;
                img->tab[i][j].G = *pixel;
                img->tab[i][j].B = *pixel;
            }
        }
    }
    fclose(file);
    return img;
}
#pragma GCC diagnostic pop