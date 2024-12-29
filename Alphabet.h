#pragma once
#include "vecteur.h"

const enum {
    NBLETTRESTOTAL = 88, ///< Nombre de lettre total se trouvant dans le jeu.
    NBLETTRESALPHABETH = 21, ///< Nombres de lettre de l'alphabeth present dans le jeu.
};



typedef struct {
    Vecteur lettres;  ///< Tableau contenant toutes les lettres de l'alphabet
}Alphabet;

extern const int letter_count[NBLETTRESALPHABETH];

/**
 * @brief Cette fonction permet d'initialiser une lettre.
 * @param[in] L Alphabeth initialiser.
 * @param[in] lettre Lettre a inserer.
 */
void InitLettres(Lettre* L, char lettre);

/**
 * @brief Cette fonction permet d'initialiser un tableau d'alphabeth pour un debut de jeu
 * @param[in] Alpha Alphabeth initialiser.
 */
void InitAlphabeth(Alphabet* Alpha);

/**
 * @brief Cette fonction permet d'afficher toutes les lettres de l'alphabeth encore en jeu et leur quantités
 * @param[in] Alpha Alphabeth en jeu.
 * @sa InitAlphabeth()
 */
void AfficherAlphabeth(Alphabet* Alpha);
void AfficherAlphabethCount(Alphabet* Alpha);
/**
 * @brief Cette fonction renvoie le nombre de lettres restant dans cet alphabeth
 * @param[in] Alpha Alphabeth utiliser
 * @return La somme de la recurrence restante de chacun des lettres.
 */
int NbLettreRestantAlphabet(const Alphabet* Alpha);

/**
 * @brief Cette fonction permet d'afficher une lettre.
 * @param[in] L Lettre que l'on souhaite afficher.
 * @sa InitLettres()
 * return La lettre.
 */
char AfficherLettre(Lettre* L);

/**
 * @brief Cette fonction permet de savoir si une lettre fait partie ou non de l'alphabeth.
 * @param [in,out] Alpha Alphabeth repertoriant les lettres et le nombre.
 * @param[in] L Lettre rechercher.
 * @return Cette fonction renvoie un booleen selon si la lettre est presente dans l'alphabeth ou non.
 * @sa InitAlphabeth()
* @pre L'alphabeth doit avoir été initialiser
*/
int est_presente(const Alphabet* Alpha, const char L);

/**
* @brief Cette fonction permet de connaire le nombre d'occurence d'une lettre dans un alphabet.
* @param[in] Alpha Alphabeth repertoriant les lettres.
* @param[in] lettre Lettre dont le nombre d'occurence est recherché.
* @return Le nombre d'occurence de la lettre.
*/
int countLettre(const Alphabet* Alpha, char lettre);

/**
 * @brief Cette fonction permet d'enlever le compte d'une lettre ayant ete defausser.
 * @param [in,out] Alpha Alphabeth repertoriant les lettres.
 * @param[in] L Lettre ayant ete defausser du jeu.
 * @sa InitAlphabeth()
 * @sa est_presente()
 * @pre La lettre <code>L</code> doit faire partie des lettres presentes dans le jeu.
 * @pre L'alphabeth doit avoir été initialiser
 */
void MoinsAlpha(Alphabet* Alpha, char L);


/**
 * @brief Cette fonction permet d'd'ajouter le compte d'une lettre ayant ete defausser.
 * @param [in,out] Alpha Alphabeth repertoriant les lettres et le nombre.
 * @param[in] L Lettre ayant ete ajouter du jeu.
 * @sa InitAlphabeth()
 * @sa est_presente()
 * @pre La lettre <code>L</code> doit faire partie des lettres presentes dans le jeu.
 * @pre L'alphabeth doit avoir été initialiser
 */
void PlusAlpha(Alphabet* Alpha, char L);


void LibererAlphabeth(Alphabet* alpha);