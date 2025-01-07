#pragma once

extern const char *DICTIONAIRE; ///Le nom du dictionnaire

const char *MOTJOUE;

/**
 * @brief Affiche le contenu d'un fichier ligne par ligne
 * @param[in] fichier Le nom du fichier à lire
 */
void afficher_fichier(const char *fichier);

/**
 * @brief Vérifie qu'un mot est dans le dictionnaire
 * @param[in] dico_file Le nom du fichier dictionnaire à lire
 * @param[in] word Le mot à rechercher dans le dictionnaire
 * @return Vrai si le mot est présent dans le dictionnaire, faux sinon
 */
int est_dans_dico(const char *dico_file, const char *word);

/**
 * @brief Écrase le contenu d'un fichier
 * @param[in] fichier Le nom du fichier à écraser
 */
void effacer_fichier(const char *fichier);

/**
 * @brief Écrit à la fin d'un fichier
 * @param[in] fichier Le nom du fichier où écrire
 * @param[in] mot La chaîne de caractères à écrire dans le fichier
 */
void ecrire_dans(const char *fichier, const char* mot);
