#pragma once
#include "vecteur.h"

const enum {
    NBLETTRESTOTAL = 88, ///< Nombre de lettres total se trouvant dans le jeu.
    NBLETTRESALPHABET = 21, ///< Nombre de lettres de l'alphabet présent dans le jeu.
};


typedef struct {
    Vecteur lettres;  ///< Tableau contenant toutes les lettres de l'alphabet
}Alphabet;

extern const int letter_count[NBLETTRESALPHABET];

/**
 * @brief Cette fonction permet d'initialiser une lettre.
 * @param[in,out] L Adresse de l'alphabet initalisé.
 * @param[in] lettre Lettre a inserer.
 */
void InitLettres(Lettre* L, char lettre);

/**
 * @brief Cette fonction permet d'initialiser un tableau d'alphabet pour un début de jeu
 * @param[out] Alpha L'adresse de l'alphabet initialisé.
 */
void InitAlphabet(Alphabet* Alpha);

/**
 * @brief Cette fonction permet d'afficher toutes les lettres de l'alphabet encore en jeu.
 * @param[in] Alpha L'adresse de l'alphabet en jeu.
 * @sa InitAlphabet()
 */
void AfficherAlphabet(Alphabet* Alpha);

/**
 * @brief Cette fonction permet d'afficher toutes les lettres de l'alphabet et leurs quantités.
 * @param[in] Alpha L'adresse de l'alphabet.
 * @sa InitAlphabet()
 */
void AfficherAlphabetCount(const Alphabet* Alpha);

/**
 * @brief Cette fonction renvoie le nombre de lettres restant dans cet alphabet
 * @param[in] Alpha Adresse de l'alphabet utilisé
 * @return La somme de la récurrence restante de chacun des lettres.
 */
int NbLettreRestantAlphabet(const Alphabet* Alpha);

/**
 * @brief Cette fonction permet d'afficher une lettre.
 * @param[in] L L'adresse de la lettre que l'on souhaite afficher.
 * @sa InitLettres()
 * return La lettre.
 */
char AfficherLettre(const Lettre* L);

/**
 * @brief Cette fonction permet de savoir si une lettre fait partie ou non de l'alphabet.
 * @param [in,out] Alpha Adresse de l'alphabet répertoriant les lettres et le nombre.
 * @param[in] L Lettre recherchée.
 * @return Cette fonction renvoie un booléen selon si la lettre est présente dans l'alphabet ou non.
 * @sa InitAlphabeth()
* @pre L'alphabet doit avoir été initialisé
*/
int est_presente(const Alphabet* Alpha, const char L);

/**
* @brief Cette fonction permet de connaître le nombre d'occurences d'une lettre dans un alphabet.
* @param[in] Alpha Adresse de l'alphabet répertoriant les lettres.
* @param[in] lettre Lettre dont le nombre d'occurences est recherché.
* @return Le nombre d'occurences de la lettre.
*/
int countLettre(const Alphabet* Alpha, char lettre);

/**
 * @brief Cette fonction permet d'enlever le compte d'une lettre ayant été défaussée.
 * @param [in,out] Alpha Adresse de l'alphabet répertoriant les lettres.
 * @param[in] L Lettre ayant été défaussée du jeu.
 * @sa InitAlphabet()
 * @sa est_presente()
 * @pre La lettre <code>L</code> doit faire partie des lettres présentes dans le jeu.
 * @pre L'alphabet doit avoir été initialisé
 */
void MoinsAlpha(Alphabet* Alpha, char L);


/**
 * @brief Cette fonction permet d'ajouter le compte d'une lettre ayant été défaussée.
 * @param [in,out] Alpha Adresse de l'alphabet répertoriant les lettres et leur nombre.
 * @param[in] L Lettre ayant été ajoutée du jeu.
 * @sa InitAlphabet()
 * @sa est_presente()
 * @pre La lettre <code>L</code> doit faire partie des lettres présentes dans le jeu.
 * @pre L'alphabet doit avoir été initialisé
 */
void PlusAlpha(Alphabet* Alpha, char L);


/**
 * @brief Désalloue une mémoire allouée dynamiquement pour un alphabet
 * @param[out] alpha L'adresse de l'alphabet à libérer
 */
void LibererAlphabeth(Alphabet* alpha);