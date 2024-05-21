#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../include/option_main.h"

void print_help() 
{
    printf("Usage: ./program <input> [--outfile=filename] [--sample=h1xv1,h2xv2,h3xv3] [--t] [--v] [--help]\n");
    printf("Options:\n");
    printf("--help : pour de l'aide ;)\n");
    printf("--outfile=filename : tu mets le blaze du fichier de sortie et surtout on oublie pas le .jpg\n");
    printf("--sample=h1xv1,h2xv2,h3xv3 : tu me give le sous echatillonnage mon gazo \n");
    printf("--v : pour activer le mode verbose\n");
    printf("--t : pour activer le mode téléchargement\n");
}

char *copie_mot_jpeg(const char *s) 
{
    size_t len = strlen(s) + 1;
    char *sortie = malloc(len);
    if (sortie) 
    {
        memcpy(sortie, s, len);
    }
    strcat(sortie, ".jpg");
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
        // output = realloc(output, taille + strlen(sample_factors) + 1);
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
        return mes_arguments;
    }
    
    char *input = NULL;
    char *output = NULL;
    char *sample_factors = NULL;
    bool couleur = false;
    bool verbose = false;
    bool progression = false;
    bool st = false;

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
            input = argv[i];
        }
    }

    if (!input) 
    {
        printf("Error: Il me faut quand même un fichier je t'avoue !!\n");
        print_help();
        return mes_arguments;
    }
    char *point = strrchr(input, '.');
    couleur = strcmp(point, ".ppm") == 0;
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
            output = copie_mot_jpeg(input); //n'existe pas dans la librairie standard 
            
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
