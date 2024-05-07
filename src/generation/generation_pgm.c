#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

char *ajout(char *chaine, uint16_t taille)
{
    /*
    On ajoute 1 en binaire à la chaine de caractère
    */
    int i = taille - 1;
    while (i >= 0 && chaine[i] == '1')
    /*
    on cherche le premier 0 en partant de la fin en s'assurant que nous somme dans les limites de la chaine
    */ 
    {
        chaine[i] = '0'; // on remplace les 1 par des 0
        i--;
    }
    if (i >= 0)
    {
        chaine[i] = '1'; // on remplace le 0 par 1
    }
    return chaine;
}

void* creation_meme_valeur(void * s, int c, size_t taille)
{   /*
    Fonction qui permet de remplir une chaine de caractère avec une seule valeur
    Intéressant quand nous voulons voir toutes les valeurs possibles d'une image et donc voir tout les cas possibles (2**64 cas possibles pour une image de 8x8 pixels)
    */
    unsigned char* chaine = (unsigned char *) s;
 
    for(size_t i = 0; i <= taille; i+=1)
    {
        chaine[i] = (unsigned char)c; // on remplit la chaine avec la valeur c afin d'avoir une image avec une seule valeur
    }
    return s;
}

void* creation_valeur_aleatoire(void * s, size_t taille)
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

char* donne_nom(uint16_t numero, bool aleatoire, uint16_t hauteur, uint16_t largeur)
{
    /*
    On donne un nom qui informe si l'image est aléatoire ou non et le numéro de l'image
    */
    char* nom = malloc(100 * sizeof(char));
    char* est_aleatoire = aleatoire ? "alea_" : "pas_alea_";
    sprintf(nom, "./images/our_images/%simage%d_%dx%d.pgm", est_aleatoire, numero, hauteur, largeur);
    return nom;
}

char* donne_nom_check(uint16_t numero, uint16_t hauteur, uint16_t largeur) {
    /*
    On donne un nom au fichier en fonction de son numéro et de ses dimensions
    */
    char* nom = malloc(100 * sizeof(char));
    sprintf(nom, "./images/our_images/checkerboard%d_%dx%d.pgm",numero, hauteur, largeur);
    return nom;
}

void generation_checkerboard(uint16_t nombre, uint16_t ligne, uint16_t colonne) {
    while (nombre > 0) 
    {   
        char* nom_ficher = donne_nom_check(nombre, ligne, colonne);
        FILE *fichier = fopen(nom_ficher, "w");
        ajout_entete(fichier, ligne, colonne);

        bool black = true;
        for (int y = 0; y < ligne; y++) {
            for (int x = 0; x < colonne; x++) {
                unsigned char pixel_value = black ? 0 : 255;
                fwrite(&pixel_value, sizeof(unsigned char), 1, fichier);
                black = !black;
            }
            if (colonne % 2 == 0)  // Pour avoir un vrai quadrillage
                black = !black;
        }
        fclose(fichier);
        nombre--;
    }
}

void generation_pgm(bool aleatoire, uint32_t taille, uint16_t nb_images, uint16_t ligne, uint16_t colonne)
{
    char FIN[taille + 1];
    creation_meme_valeur(FIN, '1', taille); // la valeur de fin est remplie de 1

    char debut[taille + 1]; // On choisit entre une valeur initale aléatoire ou non
    creation_meme_valeur(debut, '0', taille);

    FILE *fichier = NULL;
    uint16_t compteur = 0;
    while (compteur != nb_images && (strcmp(debut, FIN) != 0 || aleatoire)) // si on donne des valeurs aléatoires alors on ne s'intéresse pas au texte de fin
    /*
    Dans tout les cas on s'arrete quand on a atteint le nombre d'images demandées
    et si nous ne sommes pas aléatoires alors on s'arrête quand le texte à atteint la valeur de fin
    */
    {
        FILE *fichier = NULL;
        char* nom_ficher = donne_nom(compteur, aleatoire, ligne, colonne); // on donne un nom au fichier
        printf("%s : %d/%d\n", nom_ficher, compteur + 1, nb_images);
        fichier = fopen(nom_ficher, "w"); // on ouvre le fichier en écriture

        ajout_entete(fichier, ligne, colonne); // on ajoute l'en-tête du fichier

        if (aleatoire) // On change la valeur en focntion de si elle est aléatoire ou non
        {
            creation_valeur_aleatoire(debut, taille); 
        }
        else
        {
            ajout(debut, taille);
        }

        afficher(debut, taille, fichier); // on ajoute les valeurs de la chaine de caractère dans le fichier
        
        fclose(fichier);// on ferme le fichier

        compteur++;
    }
    if (compteur != nb_images)
    {
        afficher(FIN, taille, fichier);
    }
}


int main(int argc, char const *argv[])
{
    /*
    Ici on génère des images de taille 8x8 avec des valeurs aléatoires
    le nombre d'images générées est définie par la variable nombre donnée ci-dessous
    on choisit soit de faire des tests aléatoires ou non. 
    */

    if (argc != 5)
    {
        printf("Veuillez entrer le format : ./generation_pgm y/n nombre ligne colonne\n");
        printf("y : checkerboard\n");
        printf("n : aléatoire\n");
    }
    sleep(1);
    srand(time(NULL));
    char alea = argv[1][0];
    uint16_t nombre = atoi(argv[2]);
    uint16_t ligne = atoi(argv[3]);
    uint16_t colonne = atoi(argv[4]);
    uint32_t taille = ligne * colonne;
    if (alea == 'y')
    {
        generation_checkerboard(nombre, ligne, colonne);
    }
    else
    {   
        bool alea = true;
        generation_pgm(alea, taille, nombre, ligne, colonne);
    }

    return 0;
}