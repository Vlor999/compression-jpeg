#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include "../include/option_main.h"

void print_help() 
{
    printf("Usage: ./program <input> [--outfile=filename] [--sample=h1xv1,h2xv2,h3xv3] [--t] [--v] [--st] [--help]\n");
    printf("Options:\n");
    printf("--help : pour de l'aide ;)\n");
    printf("--outfile=filename : tu mets le blaze du fichier de sortie et surtout on oublie pas le .jpg\n");
    printf("--sample=h1xv1,h2xv2,h3xv3 : tu me give le sous echatillonnage mon gazo \n");
    printf("--v : pour activer le mode verbose\n");
    printf("--t : pour activer le mode téléchargement\n");
    printf("--st : pour activer le mode sample title : sample dans le titre\n");
}

char *copie_mot_jpeg(const char *s, bool extention) 
{
    size_t len = strlen(s) + 1;
    char *sortie = malloc(len);
    if (sortie) 
    {
        memcpy(sortie, s, len);
    }
    if(extention)
    {
        strcat(sortie, ".jpg");
    }
    return sortie;
}

char* transfo_titre(char* output, bool st, char* sample_factors) 
{ 
    if(st)
    {
        char* end = ".jpg";
        uint8_t taille = strlen(output);
        char final[taille + strlen(sample_factors) + 1];
        for (uint16_t i = 0; i < strlen(output) - 4; i++)
        {
            final[i] = output[i];
        }
        final[taille - 4] = '_';

        for (uint16_t i = 0; i < strlen(sample_factors); i++)
        {
            final[i + taille - 3] = sample_factors[i];
        }
        for(uint8_t i = 0; i < 4; i++)
        {
            final[i + taille + 8] = end[i];
        }
        output = malloc(taille + strlen(sample_factors) + 1);
        for(uint8_t i = 0; i < taille + strlen(sample_factors) + 1; i++)
        {
            output[i] = final[i];
        }
        return output;
    }
    else
    {
        return output;
    }
}

Arguments utilisation_argument(int argc, char *argv[]) 
{
    Arguments mes_arguments = {NULL, NULL, NULL, false, false, false};
    if (argc < 2) 
    {
        printf("Erreur : Il me faut un fichier gros BG\n");
        print_help();
        exit(1);
    }
    
    char *input = NULL;
    char *output = NULL;
    char *sample_factors = NULL;
    bool couleur = false;
    bool verbose = false;
    bool progression = false;
    bool st = false;

    uint8_t nb = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) 
        {
            print_help();
            return mes_arguments;
        } 
        else if (strncmp(argv[i], "--outfile=", 10) == 0) 
        {
            output = argv[i] + 10;
        } 
        else if (strncmp(argv[i], "--sample=", 9) == 0) 
        {
            sample_factors = argv[i] + 9; 
        } 
        else if (strcmp(argv[i], "--v") == 0)
        {
            verbose = true;
        }
        else if (strcmp(argv[i], "--t") == 0)
        {
            progression = true;
        }
        else if (strcmp(argv[i], "--st") == 0)
        {
            st = true;
        }
        else 
        {
            nb++;
            input = argv[i];
            if (nb > 1) 
            {
                printf("Erreur: les arguments sont mauvais\n");
                print_help();
                exit(1);
            }
        }
    }
    if (!input) 
    {
        printf("Error: Il me faut quand même un fichier je t'avoue !!\n");
        print_help();
        exit(1);
    }
    else
    {
        if (access(input, R_OK ) != -1)
        {
            printf("Le fichier existe et est lisible\n");
        } 
        else 
        {
            printf("Le fichier n'existe pas ou n'est pas lisible\n");
            print_help();
            exit(1);
        }
    }
    char *point = strrchr(input, '.');
    if(point == NULL)
    {
        printf("Erreur: Le fichier d'entrée n'a pas d'extension\n");
        print_help();
        exit(1);
    }
    couleur = strcmp(point, ".ppm") == 0;
    bool gris = strcmp(point, ".pgm") == 0;
    if (!couleur && !gris) 
    {
        printf("Erreur: Le fichier d'entrée n'est pas un fichier PPM ou PGM\n");
        print_help();
        exit(1);
    }
    if (!output) 
    {
        if(point) 
        {
            size_t input_len = point - input;
            output = malloc((input_len + 5)*sizeof(char));
            strncpy(output, input, input_len);
            output[input_len] = '\0';
            output = strcat(output, ".jpg");
        } 
        else 
        {
            output = copie_mot_jpeg(input, true);
        }
    }
    else
    {
        char* ext = strrchr(output, '.');
        if (ext == NULL || strcmp(ext, ".jpg") != 0) 
        {
            printf("Erreur: Le fichier de sortie n'est pas un fichier JPEG\n");
            print_help();
            exit(1);
        }
        output = copie_mot_jpeg(output, false);
        if (access(output, F_OK ) != -1)
        {
            printf("Nous ne pouvons pas écrire dans le fichier\n");
            print_help();
            exit(1);
        }
    }

    if(sample_factors == NULL) 
    {
        sample_factors = "1x1,1x1,1x1";
    }

    char* new_titre = transfo_titre(output, st, sample_factors);
    mes_arguments.input = input;
    mes_arguments.output = new_titre;
    mes_arguments.sample_factors = sample_factors;
    mes_arguments.couleur = couleur;
    mes_arguments.verbose = verbose;
    mes_arguments.progression = progression;
    return mes_arguments;
}
