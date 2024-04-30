
/**
 * @brief Fonction qui permet de parcourir une matrice en zigzag
 * @param matrice la matrice à parcourir
 * @return un tableau 1D de taille 64
 * **/

double* zigzag_matrice(double** matrice);

/**
 * @brief Fonction qui permet de parcourir une matrice en zigzag mais sans boucle
 * @param matrice la matrice à parcourir
 * @return un tableau 1D de taille 64
 * **/

double* zigzag_matrice1(double** matrice);

/**
 * @brief recupère le tableau après zig zag et applique codage RLE
 * @param tab le tableau donnée après zigzag !! l'indice 0 correspond à la taille du tableau
 * @return un tableau 1D plus court 
 * **/

double* codage_RLE(double* tab);
