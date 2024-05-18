#ifndef OPTION_MAIN_H
#define OPTION_MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char* input;
    char* output;
    char* sample_factors;
    bool couleur;
    bool verbose;
    bool progression;
} Arguments;

/*
* @param : const char *s
* @return : char *
* @brief : permet de dupliquer une chaine de caractère et de rajouter.jpeg à la fin
*/
char *copie_mot_jpeg(const char *s);

/*
* @param : pas d'argument
* @return : rien 
* @brief : affiche l'aide sur l'utilisation du programme 
*/
void print_help();

/*
* @param : int argc, char *argv[]
* @return : Arguments
* @brief : permet de récuérer les arguments de la ligne de commande utiliser dans le main
*/
Arguments utilisation_argument(int argc, char *argv[]);

#endif