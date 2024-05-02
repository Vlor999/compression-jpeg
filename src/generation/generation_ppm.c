#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generatePPM(const char *filename, int largeur, int hauteur) {
    FILE *file = fopen(filename, "w");
    fprintf(file, "P3\n%d %d\n255\n", largeur, hauteur);


    for (int y = 0; y < hauteur; y++) {
        for (int x = 0; x < largeur; x++) {
            // Génération de valeurs RGB aléatoires
            int r = rand() % 256;
            int g = rand() % 256;
            int b = rand() % 256;
            fprintf(file, "%d %d %d ", r, g, b);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

int main(int argc, char *argv[]) 
{

    srand(time(NULL)); // Initialisation du générateur de nombres aléatoires avec une graine basée sur l'heure actuelle

    if (argc != 4) {
        printf("Utilisation: %s <largeur> <hauteur> <nombre_images>\n", argv[0]);
        return 1;
    }

    const char *prefixe_nom = "./images/our_images/image_aleatoire";
    int largeur = atoi(argv[1]);
    int hauteur = atoi(argv[2]);
    int nombre_images = atoi(argv[3]);

    for (int i = 1; i <= nombre_images; i++) {
        char filename[50]; // Taille suffisante pour stocker le nom de fichier
        sprintf(filename, "%s%d_%dx%d.ppm", prefixe_nom, i, largeur, hauteur);
        generatePPM(filename, largeur, hauteur);
        printf("Image %s générée avec succès.\n", filename);
    }

    return 0;
}
