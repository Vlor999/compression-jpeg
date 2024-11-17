# Projet JPEG - 1A  
**Team 6**  
- Willem Adnet  
- Édouard Da Cruz  
- Hugo Zabiego  

## Introduction  

Ce projet a pour objectif de convertir une image au format **PPM/PGM** en une image compressée au format **JPEG**. Nous détaillons ici les étapes clés du projet ainsi que les choix techniques et méthodologiques adoptés.

## Découpage des fonctionnalités du projet  

1. **Lecture et génération d'images**  
   - Lecture des images PPM/PGM à partir d'un chemin spécifié.  
   - Génération d'images PPM/PGM à partir de matrices définies.  

2. **Conversion de l'image en YCbCr**  
   - Transformation des images RGB au format YCbCr.  

3. **Sous-échantillonnage**  
   - Réduction des composantes chromatiques selon des ratios prédéfinis.  

4. **Transformation DCT**  
   - Conversion des données spatiales en données fréquentielles via la transformation discrète en cosinus.  

5. **ZigZag**  
   - Réorganisation des coefficients DCT en un vecteur ligne.  

6. **Quantification**  
   - Réduction de la précision des coefficients pour maximiser la compression.  

7. **Encodage RLE**  
   - Compression des séquences de zéros en utilisant l'encodage Run-Length.  

8. **Codage Huffman**  
   - Compression des coefficients via un algorithme de codage préfixé.  

9. **Écriture de l'image compressée**  
   - Génération de fichiers conformes au standard JPEG.  

10. **Optimisation**  
    - Amélioration des performances et réduction de l'utilisation mémoire.  

## Structure des données  

Le projet repose sur une organisation modulaire et utilise des matrices et vecteurs pour représenter les images à chaque étape du processus.  

## Répartition des tâches  

- **Willem Adnet** : Transformation DCT, ZigZag, et quantification.  
- **Édouard Da Cruz** : Conversion YCbCr et sous-échantillonnage.  
- **Hugo Zabiego** : Encodages RLE et Huffman, écriture JPEG.  

## Compilation et exécution  

Le projet utilise un fichier `Makefile` pour automatiser la compilation et la gestion des fichiers.  

### Commandes disponibles  

- **`make` ou `make all`** : Compile le projet et génère l'exécutable `ppm2jpeg`.  
- **`make clean`** : Supprime les fichiers objets (.o) et l'exécutable généré.  
- **`make real_clean`** : Supprime tous les fichiers générés, y compris les fichiers compressés dans les dossiers `images` et `images/our_images`.  

### Dépendances  

Le projet utilise :  
- Le compilateur GCC avec les options :  
  - `-Wall` : Affiche tous les avertissements.  
  - `-Wextra` : Affiche des avertissements supplémentaires.  
  - `-std=c99` : Force l'utilisation du standard C99.  
  - `-O2` : Optimisations de niveau 2.  
  - `-g` : Ajoute les symboles de débogage.  
- Les bibliothèques :  
  - `-lm` : Pour les calculs mathématiques.  
  - `-lpthread` : Pour les threads POSIX.  

### Structure des fichiers  

- **Code source** : Les fichiers `.c` sont dans le dossier `src/`.  
- **Fichiers objets** : Générés dans le dossier `obj/`.  
- **Exécutable** : Produit final nommé `ppm2jpeg`.  

## Limitations  

- La compression peut être inefficace pour les très petites images.  
- Quelques problèmes subsistent dans la gestion mémoire, nécessitant une attention future.  

## Conclusion  

Le projet illustre les concepts fondamentaux de la compression JPEG tout en mettant en lumière les défis techniques associés à sa mise en œuvre. Les prochaines étapes incluraient des optimisations supplémentaires pour une meilleure gestion des ressources.

---  
**Note** : Ce projet a été réalisé dans le cadre de notre première année d'étude et peut servir de base pour des travaux ultérieurs en traitement d'image.
