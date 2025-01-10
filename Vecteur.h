#pragma once

#include "Item_Vecteur.h"

/**
 * @brief Conteneur stockant des  l ments accessibles en
 * fonction de leur position (indice).
 */
typedef struct {
	int nbElements; ///< Nombre d' l ments pr sents dans le vecteur.
	int capacite;	///< Nombre d' l ments maximal du vecteur.
	Lettre* elements; ///< Tableau (dynamique) de taille <code>capacite</code>.
}Vecteur;

/**
 * @brief Initialise un vecteur d'une capacit  donn e contenant aucun  l ment.
 * Apr s son utilisation, la m moire occup e par un vecteur doit  tre lib r e
 * en invoquant la fonction @ref detruireVecteur.
 * @param[out] v L'adresse du vecteur   initialiser.
 * @param[in] capacite La capacit  initiale du vecteur.
 * @return 0 en cas d' chec (manque de m moire disponible) et 1 en cas de succ s.
 * @pre <code>capacite</code> doit  tre sup rieur ou  gal   1.
 */
int initVecteur(Vecteur* v, int capacite);

/**
 * @brief Retourne le nombre d' l ments pr sents dans un vecteur.
 * @param[in] v L'adresse du vecteur.
 * @return Le nombre d' l ments contenu dans <code>v</code>.
 */
int taille(const Vecteur* v);

/**
 * @brief Ajoute un  l ment dans un vecteur. Cet  l ment est ajout  apr s ceux d j  pr sents.
 * @param[in,out] v L'adresse du vecteur.
 * @param[in] it L' l ment devant  tre ajout .
 * @return 0 en cas d' chec (manque de m moire disponible) et 1 en cas de succ s.
 */
int ajouter(Vecteur* v, Lettre it);

/**
 * @brief Retourne l' l ment d'un vecteur se trouvant   une position donn e.
 * @param[in] v L'adresse du vecteur.
 * @param[in] i La position (i.e. l'indice).
 * @return L' l ment de <code>v</code> se trouvant   l'indice <code>i</code>.
 * @pre La valeur de <code>i</code> doit  tre comprise entre 0 et
 * <code>(taille(v) - 1)</code> (inclus).
 */
Lettre obtenir(const Vecteur* v, int i);

/**
 * @brief Modifie un  l ment d'un vecteur.
 * @param[in,out] v L'adresse du vecteur.
 * @param[in] i La position (i.e. l'indice) de l' l ment devant  tre modifi .
 * @param[in] it La nouvelle valeur de l' l ment.
 * @pre La valeur de <code>i</code> doit  tre comprise entre 0 et
 * <code>(taille(v) - 1)</code> (inclus).
 */
//void modifier(Vecteur* v, int i, ItemV it);

/**
 * @brief Supprime un  élément d'un vecteur.
 * @param[in,out] v L'adresse du vecteur.
 * @param[in] i La position (i.e. l'indice) de l' l ment devant  tre supprim .
 * @pre La valeur de <code>i</code> doit  tre comprise entre 0 et
 * <code>(taille(v) - 1)</code> (inclus).
 */
void supprimer(Vecteur* v, int i);

/**
 * @brief Modifie la capacit  courante d'un vecteur. Si la nouvelle capacit  du vecteur
 * exc de le nombre d' l ments qu'il contient, tous ses  l ments sont conserv s. Dans
 * le cas contraire, les  l ments exc dentaires sont perdus.
 * @param[in,out] v L'adresse du vecteur.
 * @param[in] taille La nouvelle capacit .
 * @return 0 en cas d' chec (manque de m moire disponible) et 1 en cas de succ s.
 * @pre La nouvelle capacit  doit  tre sup rieure ou  gale   1.
 */
int retailler(Vecteur* v, int taille);

/**
 * @brief Lib re l'espace m moire occup  par un vecteur. Apr s avoir  t  d truit, il ne doit
 * pas  tre r -employ  sans avoir  t  r -initialis . Toute autre op ration peut donner des
 * r sultats incoh rent ou m me provoquer l'arr t brutal du programme.
 * @param[in,out] v L'adresse du vecteur.
 */
void detruireVecteur(Vecteur* v);
