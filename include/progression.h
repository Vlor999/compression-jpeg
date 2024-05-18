#ifndef PROGRESSION_H
#define PROGRESSION_H
#include <stdio.h>
#include <stdint.h>
#include <../include/recup_v2.h>
#include <../include/option_main.h>

void affiche_data(data_frame our_datas, Arguments mes_arguments);

uint64_t taille_fichier(const char *nom_fichier);

void affiche_progression(uint64_t max_valeur, uint64_t nb_valeur);

#endif