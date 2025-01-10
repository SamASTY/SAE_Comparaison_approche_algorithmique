#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Dictionaire.h"

enum { TAILLEMAXMOT = 100 };

const char *DICTIONAIRE = "ods4.txt";

const char *MOTJOUE = "MotDejaJouer.txt";

int est_dans_dico(const char *dico_file, const char *word) {
    FILE *file = fopen(dico_file, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier dictionnaire");
        return 0;
    }

    char mot[TAILLEMAXMOT];
    while (fgets(mot, sizeof(mot), file)) {
        mot[strcspn(mot, "\n")] = '\0';
        while (mot[strlen(mot) - 1] == ' ') {
            mot[strlen(mot) - 1] = '\0';
        }

        if (strcmp(mot, word) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void afficher_fichier(const char *fichier) {
    FILE *file = fopen(fichier, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier dictionnaire");
        return;
    }

    char *mot = malloc(TAILLEMAXMOT * sizeof(char));  // Tampon dynamique pour chaque mot
    if (mot == NULL) {
        perror("Erreur d'allocation mémoire");
        fclose(file);
        return;
    }

    while (fgets(mot, TAILLEMAXMOT, file)) {
        mot[strcspn(mot, "\n")] = '\0';

        printf("%s\n", mot);
    }

    free(mot);
    fclose(file);
}

void ecrire_dans(const char *fichier, const char* mot) {
    FILE *file = fopen(fichier, "a");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }
    fprintf(file, "%s\n", mot);
    fclose(file);
}

void effacer_fichier(const char *fichier) {
    FILE *file = fopen(fichier, "w"); // Ouvre le fichier en mode écriture pour l'effacer
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }
    fclose(file);
}