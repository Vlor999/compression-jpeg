#!/bin/bash

# Compilation du programme C
gcc -Wextra -Wall -g src/generation/generation_pgm.c -o generate_pgm

# Vérification de la réussite de la compilation
if [ $? -eq 0 ]; then
    echo "Compilation réussie. Génération des images..."
else
    echo "Erreur lors de la compilation. Arrêt du processus."
    echo "format : ./make_generation_pgm.sh <num> <nb_images> <nb_lignes> <nb_colonnes> "
    exit 1
fi

./generate_pgm "$1" "$2" "$3" "$4" "$5"

# Suppression de l'exécutable
rm generate_pgm
