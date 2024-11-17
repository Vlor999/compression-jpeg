# Compilateur et options
CC = gcc
LD = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude -O2 -g
LDFLAGS = -lm

# Fichiers source et objets
SRC_DIR = src
OBJ_DIR = obj
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Cible par défaut
all: ppm2jpeg

# Cible principale : construction de l'exécutable
ppm2jpeg: $(OBJ_FILES)
	@echo "Édition des liens pour créer l'exécutable : $@"
	$(LD) $(OBJ_FILES) $(LDFLAGS) -o $@

testAll: ppm2jpeg
	@echo "Lancement des tests"
	./execution_all

# Règle de construction des fichiers objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)  # Création du dossier obj si nécessaire
	@echo "Compilation de $< -> $@"
	$(CC) -c $(CFLAGS) $< -o $@

# Nettoyage des fichiers objets et exécutables
.PHONY: clean
clean:
	@echo "Nettoyage des fichiers objets et de l'exécutable"
	rm -rf ppm2jpeg $(OBJ_DIR)/*.o

# Nettoyage complet
.PHONY: real_clean
real_clean: clean
	@echo "Nettoyage complet (fichiers générés et résultats)"
	rm -rf $(OBJ_DIR) images/*.jpg images/*.bla images/our_images/*.jpg images/our_images/*.bla
