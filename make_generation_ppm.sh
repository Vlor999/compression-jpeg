#!/bin/bash

# Compilation du programme C
gcc -Wextra -Wall -g src/generation/generation_ppm.c -o generate_ppm

# Vérification de la réussite de la compilation
if [ $? -eq 0 ]; then
    echo "Compilation réussie. Génération des images..."
else
    echo "Erreur lors de la compilation. Arrêt du processus."
    echo "format : ./make_generation_ppm.sh <nb_lignes> <nb_colonnes> <nb_images>"
    exit 1
fi

./generate_ppm "$1" "$2" "$3" 

# Suppression de l'exécutable
rm generate_ppm
