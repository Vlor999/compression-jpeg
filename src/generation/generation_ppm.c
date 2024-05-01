#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void* creation_valeur_aleatoire(void* s, size_t taille)
{
    /*
    Fonction assez similaire sauf q'ici on remplit la chaine avec des valeurs aléatoires
    Chaque valeur est soit 0 ou 1
    */
    unsigned char* chaine = (unsigned char *) s;
 
    for(size_t i = 0; i < taille; i+=1)
    {
        chaine[i] = abs(rand()% 256); // on remplit la chaine avec des valeurs aléatoires
    }
    return s;
}

void afficher(char *chaine, uint32_t taille, FILE* fichier)
{
    /*
    Renvoie dans le fichier les valeurs de la chaine de caractère
    */
    fwrite(chaine, sizeof(unsigned char), taille, fichier);
    fprintf(fichier, "\n");
}

void ajout_entete(FILE *fichier, uint16_t nb_ligne, uint16_t nb_colonne)
{
    /*
    Création de l'en-tête du fichier pgm
    */
    fprintf(fichier, "P5\n");
    fprintf(fichier, "%d %d\n", nb_ligne, nb_colonne);
    fprintf(fichier, "255\n");
}

char* donne_nom(uint16_t numero)
{
    /*
    On donne un nom qui informe si l'image est aléatoire ou non et le numéro de l'image
    */
    char* nom = malloc(100 * sizeof(char));
    sprintf(nom, "./images/our_images/alea_image%d.ppm", numero);
    return nom;
}

void generation_pgm(uint32_t taille, uint16_t nb_images, uint16_t ligne, uint16_t colonne)
{
    char debut[taille + 1]; // On choisit entre une valeur initale aléatoire ou non
    creation_meme_valeur(debut, '0', taille);

    FILE *fichier = NULL;
    uint16_t compteur = 0;
    while (compteur != nb_images) // si on donne des valeurs aléatoires alors on ne s'intéresse pas au texte de fin
    /*
    Dans tout les cas on s'arrete quand on a atteint le nombre d'images demandées
    et si nous ne sommes pas aléatoires alors on s'arrête quand le texte à atteint la valeur de fin
    */
    {
        FILE *fichier = NULL;
        char* nom_ficher = donne_nom(compteur); // on donne un nom au fichier
        printf("%s : %d/%d\n", nom_ficher, compteur + 1, nb_images);
        fichier = fopen(nom_ficher, "w"); // on ouvre le fichier en écriture

        ajout_entete(fichier, ligne, colonne); // on ajoute l'en-tête du fichier

        creation_valeur_aleatoire(debut, taille); 
        

        afficher(debut, taille, fichier); // on ajoute les valeurs de la chaine de caractère dans le fichier
        
        fclose(fichier);// on ferme le fichier

        compteur++;
    }
}


int main(int argc, char const *argv[])
{
    /*
    Ici on génère des images de taille 8x8 avec des valeurs aléatoires
    le nombre d'images générées est définie par la variable nombre donnée ci-dessous
    on choisit soit de faire des tests aléatoires ou non. 
    */
    if (argc != 4)
    {
        printf("Veuillez entrer le format : ./generation_pgm nombre ligne colonne\n");
    }

    srand((unsigned int)time(NULL));

    uint16_t nombre = atoi(argv[1]);
    uint16_t ligne = atoi(argv[2]);
    uint16_t colonne = atoi(argv[3]);

    uint32_t taille = ligne * colonne;
    generation_pgm(taille, nombre, ligne, colonne);
    return 0;
}