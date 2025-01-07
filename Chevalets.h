#pragma once
#include "Alphabet.h"

const enum {
    NBLETTREJOUEURDEBUT = 12, ///< Nombre de lettres que chaque joueur reçoit en début de partie.
    TAILLEMAXMOT = 8, ///Taille maximale qu'un·e joueur·se peut insérer sur le rail.
};

typedef struct {
    Vecteur lettres; ///< Lettre appartenant au/à la joueur·se.
}PAQUETS;

/**
 * @brief Cette fonction permet de proposer une lettre aléatoirement choisie dans un paquet de cartes.
 * @param[in] Alpha L'adresse de l'alphabet en jeu
 * @param[out] L L'adresse de la lettre piochée
 */
char piochePaquet(Alphabet* Alpha, Lettre* L);

/**
 * @brief Cette fonction permet d'initialiser le début de jeu en distribuant au deux joueur·ses leurs chevalets.
 * @param[in] Alpha L'adresse d'un alphabet initialisé uniquement pour la distribution.
 * @param[out] joueur1 Adresse du paquet du/de la premier·e joueur·se.
b* @param[out] joueur2 Adresse du paquet du/de la second·e joueur·se.
 * @pre L'alphabet doit être initialisé au préalable et doit contenir des lettres
 * @sa DistribuerLettre()
 */
void InitPartie(Alphabet* Alpha, PAQUETS* joueur1, PAQUETS* joueur2);

void InitPartiedejfait(PAQUETS* joueur1, PAQUETS* joueur2);

/**
 * @brief Cette fonction permet d'afficher le contenu d'un paquet trié par ordre alphabétique.
 * @param[in] paquet L'adresse du paquet que l'on souhaite afficher.
 * @pre Le paquet doit faire partie d'une partie initialisée.
 */
void AfficherPaquetTrie(const PAQUETS* paquet);

/**
 * @brief Compare deux lettres (par ordre alphabétique)
 * @param[in] a L'adresse de la première lettre
 * @param[in] b L'adresse de la deuxième lettre
 * @return -1 si a < b, 0 si a = b, 1 si a > b
 */
int comparerLettre(const void* a, const void* b);

/**
 * @brief Change la pioche d'un·e joueur·se
 * @param[in,out] Alpha L'adresse de l'alphabet dans lequel repiocher
 * @param[in] L La lettre à échanger
 * @param[out] J L'adresse du paquet du/de la joueur·se qui contient L.
 */
void EchangePioche(Alphabet* Alpha, char L, PAQUETS* J);

/**
 * @brief Vérifie qu'une lettre est dans un paquet
 * @param[in] paquet L'adresse du paquet en question
 * @param[in] L La lettre en question
 * @return Vrai si la lettre est dans le paquet, faux sinon
 */
int est_dans(const PAQUETS* paquet, const char L);

/**
 * @brief Duplique un paquet
 * @param[in] source L'adresse du paquet source
 * @param[out] destination L'adresse du paquet où dupliquer le paquet source
 */
void DupliquerPaquet(const PAQUETS* source, PAQUETS* destination);

/**
 * @brief Retire une lettre d'un paquet
 * @param[out] P L'adresse du paquet duquel retirer la lettre
 * @param[in] L La lettre à retirer
 */
void MoinsPaquet(PAQUETS *P, char L);

/**
 * @brief Ajoute une lettre à un paquet
 * @param[out] P L'adresse du paquet auquel ajouter la lettre
 * @param[in] L La lettre à ajouter au paquet pointé par P
 */
void PlusPaquet(PAQUETS *P, char L);

/**
 * @brief Désalloue la mémoire allouée dynamiquement pour un paquet
 * @param P L'adresse du paquet à libérer
 */
void LibererPaquets(PAQUETS* P);

/**
 * @brief Vérifie si un paquet est vide
 * @param[in] P L'adresse du paquet à vérifier
 * @return Vrai si le paquet est vide, faux sinon
 */
int EstVide(const PAQUETS* P);

/**
 * @brief Permet d'obtenir le nombre de lettres restantes dans un paquet
 * @param[in] P L'adresse du paquet duquel mesurer la taille
 * @return La taille du paquet pointé par P
 */
int NbRestant(const PAQUETS* P);