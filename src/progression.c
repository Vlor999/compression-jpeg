#include <stdio.h>
#include <stdint.h>
#include <../include/recup_v2.h>
#include <../include/option_main.h>


void affiche_data(data_frame our_datas, Arguments mes_arguments)
{
    printf("+------------------+-----------------------+\n");
    printf("| Property         | Value                 |\n");
    printf("+------------------+-----------------------+\n");
    printf("| Input            | %20s  |\n", mes_arguments.input);
    printf("| Output           | %20s  |\n", mes_arguments.output);
    printf("| Sample Factors   | %20s  |\n", mes_arguments.sample_factors);
    printf("| Couleur          | %20d  |\n", mes_arguments.couleur);
    printf("| Verbose          | %20d  |\n", mes_arguments.verbose);
    printf("+------------------+-----------------------+\n");
    printf("| nb_ligne         | %20d  |\n", our_datas.nb_ligne);
    printf("| nb_colonne       | %20d  |\n", our_datas.nb_colonne);
    printf("| nb_MCU           | %20d  |\n", our_datas.nb_MCU);
    printf("| Maximum Value    | %20d  |\n", our_datas.maximum_value);
    printf("| Header           | %20d  |\n", our_datas.header);
    printf("| isRGB            | %20d  |\n", our_datas.isRGB);
    printf("+------------------+-----------------------+\n");
}

uint64_t taille_fichier(const char *nom_fichier)
{
    FILE *fichier = fopen(nom_fichier, "r");
    if (fichier == NULL)
    {
        return 0;
    }

    fseek(fichier, 0, SEEK_END);
    uint64_t taille = ftell(fichier);
    fclose(fichier);
    char* cond = "o";
    if (taille > 1000)
    {
        taille /= 1000;
        cond = "kb";
    }
    if (taille > 1000)
    {
        taille /= 1000;
        cond = "Mb";
    }
    if (taille > 1000)
    {
        taille /= 1000;
        cond = "Gb";
    }
    printf("Taille du fichier %s : %4lu %s\n", nom_fichier, taille, cond);
    return taille;
}

void affichage_fin(char* input, char* filename)
{
    printf("\nCompression terminée\n");
    uint64_t taille_input = taille_fichier(input);
    uint64_t taille_output = taille_fichier(filename);
    printf("Compression ratio : %ld\n", (uint64_t)taille_input / taille_output);
}

void affiche_progression(uint64_t max_valeur, uint64_t nb_valeur)
{
    uint16_t progress = (int)((nb_valeur * 100) / max_valeur);
    if (progress > 100)
    {
        progress = 100;
    }

    switch (progress % 4)
    {
        case 0:
            printf("| ");
            break;
        case 1:
            printf("/ ");
            break;
        case 2:
            printf("- ");
            break;
        case 3:
            printf("\\ ");
            break;
    }

    for (uint16_t i = 0; i < progress; i++)
    {
        printf("#");
    }

    for (uint16_t i = 0; i < 100 - progress; i++)
    {
        printf("-");
    }
    printf("[%3d%%]", progress);
    
    printf("\r");
}
