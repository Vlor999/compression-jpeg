#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_tete(FILE *file, int largeur, int hauteur) 
{
    fprintf(file, "P6\n%d %d\n255\n", largeur, hauteur);
}

void generatePPM(const char *filename, int largeur, int hauteur) {
    FILE *file = fopen(filename, "wb"); 
    generate_tete(file, largeur, hauteur);

    unsigned char *pixels = malloc(3 * largeur * hauteur * sizeof(unsigned char));

    for (int i = 0; i < largeur * hauteur * 3; i += 3) 
    {
        pixels[i] = rand() % 256;
        pixels[i + 1] = rand() % 256;
        pixels[i + 2] = rand() % 256;
    }

    fwrite(pixels, sizeof(unsigned char), 3 * largeur * hauteur, file);
    free(pixels); 
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
