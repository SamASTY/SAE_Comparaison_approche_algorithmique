#pragma once
#include "Alphabet.h"

const enum {
    NBLETTREJOUEURDEBUT = 12, ///< Nombre de lettre que chaque joueur recois en debut de partie.
    TAILLEMAXMOT = 8, ///Taille maximal qu'un joueur peux inserer sur le rail.
};

typedef struct {
    Vecteur lettres; ///< Lettre appartenant au joueur.
}PAQUETS;

/**
 * @brief Cette fonction permet de proposer une lettre aleatoirement choisi dans un paquets de carte.
 * @param[in] Alpha l'alphabeth en jeu
 * @param[out] L Lettre piocher
 */
char piochePaquet(Alphabet* Alpha, Lettre* L);

/**
 * @brief Cette fonction permet d'initialiser le debut de jeu en distribuant au deux joueurs leurs chevalets.
 * @param[in] Alpha Un alphabeth initialiser uniquement pour la distribution.
 * @param[out] joueur1 Jeu du premier joueur.
b* @param[out] joueur2 Jeu du second joueur.
 * @param[out] pioche Chevalet se trouvant dans la pioches.
 * @pre L'alphabeth doit etre initialiser au prelable et doit contenir des lettres
 * @sa DistribuerLettre()
 */
void InitPartie(Alphabet* Alpha, PAQUETS* joueur1, PAQUETS* joueur2);

void InitPartiedejfait(PAQUETS* joueur1, PAQUETS* joueur2);

/**
 * @brief Cette fonction permet d'afficher le contenu d'un paquet trier par ordre alphabetique.
 * @param[in] paquet Paquets que l'on souhaite afficher.
 * @pre Le paquet doit faire partie d'une partie initialiser.
 */
void AfficherPaquettrier(PAQUETS* paquet);

int comparerLettre(const void* a, const void* b);

void EchangePioche(Alphabet* Alpha, char L, PAQUETS* J);

int est_dans(const PAQUETS* paquet, const char L);

void DupliquerPaquet(const PAQUETS* source, PAQUETS* destination);

void MoinsPaquet(PAQUETS *P, char L);

void PlusPaquet(PAQUETS *P, char L);

void LibererPaquets(PAQUETS* P);

int EstVide(PAQUETS* P);

int NbRestant(PAQUETS* P);