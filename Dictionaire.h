#pragma once

extern const char *DICTIONAIRES;

const char *MOTJOUER;

void afficher_fichier(const char *fichier);

int est_dans_dico(const char *dico_file, const char *word);

void effaser_fichier(const char *fichier);

void ecrire_dans(const char *fichier, char* mot);
