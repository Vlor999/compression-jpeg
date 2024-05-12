#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "../include/conversionRGB.h"
#include "../include/recup_v2.h"

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
    nb_MCU = ((col + 7) / 8) * 8 * ((ligne + 7) / 8) * 8 / (MCU_TAILLE * MCU_TAILLE);

    data_frame data = {col, ligne, nb_MCU, max, header, isRGB, file};
    return data;
}

MCU_RGB *Read_File(data_frame data, uint64_t number)
{
    /*
    Correction à effectuer :
    - Il y a un porblème si le fichier n'est pas de taille divisible par 8
    - Je ne retrourne aps bien à la ligne et donc cela créer un décalage à chaque fois
    */
    uint32_t bla = number;
    FILE *file = data.file;
    uint32_t nb_colonne = data.nb_colonne;
    uint32_t nb_ligne = data.nb_ligne;

    nb_colonne = ((nb_colonne + 7) / 8) * 8;
    nb_ligne = ((nb_ligne + 7) / 8) * 8;

    uint32_t sous_matrice_par_ligne = nb_colonne / MCU_TAILLE;
    uint32_t debut_ligne = ((number - 1) / sous_matrice_par_ligne) * 8 + 1;
    uint32_t debut_colonne = ((number - 1) % sous_matrice_par_ligne) * 8 + 1;

    bool ligne_ok = debut_ligne + 7 <= data.nb_ligne;
    bool colonne_ok = debut_colonne + 7 <= data.nb_colonne;

    uint8_t max_value_i = MCU_TAILLE;
    uint8_t max_value_j = MCU_TAILLE;

    if (!ligne_ok)
    {
        max_value_i = data.nb_ligne - debut_ligne + 1;
    }
    if (!colonne_ok)
    {
        max_value_j = data.nb_colonne - debut_colonne + 1;
    }

    MCU_RGB *mcu = malloc(sizeof(MCU_RGB));
    uint8_t taille = sizeof(Triplet_RGB);
    if (!data.isRGB)
    {
        taille = sizeof(uint8_t);
    }

    long int position_debut = data.header * sizeof(uint8_t) + (debut_ligne - 1) * data.nb_colonne * sizeof(uint8_t) * taille + (debut_colonne - 1) * sizeof(uint8_t) * taille;
    fseek(file, position_debut, SEEK_SET);

    Triplet_RGB last_triplet_RGB = {0, 0, 0};
    uint8_t decalage = debut_colonne + 7 - MCU_TAILLE;

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
                    mcu->tab[i][j] = last_triplet_RGB;
                }
            }
            else
            {
                uint8_t pixel;
                if (i < max_value_i && j < max_value_j)
                {
                    fread(&pixel, taille, 1, file);
                }
                else
                {
                    pixel = last_triplet_RGB.R;
                }
                mcu->tab[i][j].R = pixel;
                mcu->tab[i][j].G = pixel;
                mcu->tab[i][j].B = pixel;
            }
            last_triplet_RGB = mcu->tab[i][j];
        }
        fseek(file, (data.nb_colonne - 8) * taille, SEEK_CUR);
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

int main(int argc, char* argv[]) {
    if (argc != 2)
    {
        printf("Mettre sous la forme : %s <filename>\n", argv[0]);
        return 1;
    }

    const char* filename = argv[1];
    imagePGM_RGB* img = LecturePPM(filename);
    if (!img) {
        printf("Failed to read PPM file: %s\n", filename);
        return 1;
    }

    uint16_t c1 = 1;
    for(uint8_t i = 0; i < 1; i+=8)
    {
        for (uint16_t l = 0; l < 2995; l+=8)
        {
            printf("numéro : %d\n", c1);
            printf("i : %d; l : %d\n", i, l);
            for(uint8_t k = 0; k < 8; k++)
            {
                for(uint8_t j = 0; j< 8; j++)
                {
                    printf("%02x %02x %02x \t", img->tab[i + k][j + l].R, img->tab[i + k][j + l].G, img->tab[i+k][j + l].B);
                }
                printf("\n");
            }
            c1++;
            printf("\n");
        }
    }

    printf("\n\n\n");
    printf("Lecture_Init\n");

    data_frame data = Lecture_Init(filename);
    uint16_t compteur = 120;

    MCU_RGB* mcu;
    while (compteur <= 150)
    {
        mcu = Read_File(data, compteur);
        printf("numéro : %d\n", compteur);
        for(uint8_t i = 0; i < MCU_TAILLE; i++)
        {
            for(uint8_t j = 0; j < MCU_TAILLE; j++)
            {
                printf("%02x %02x %02x \t", mcu->tab[i][j].R, mcu->tab[i][j].G, mcu->tab[i][j].B);
            }
            printf("\n");
        }
        printf("\n");
        compteur++;
    }
    Fermeture_fichier(data);
    return 0;
}
