#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "Vecteur.h"
#include "Alphabet.h"
#include "Chevalets.h"

#include <assert.h>

char piochePaquet(Alphabet* Alpha) {
    assert(taille(&Alpha->lettres) > 0);
    int r = rand() % taille(&Alpha->lettres);
    Lettre La = obtenir(&Alpha->lettres, r);
    char lettre =AfficherLettre(&La);
    MoinsAlpha(Alpha,lettre);
    return lettre;
}

void InitPartie(Alphabet* Alpha_jeu, PAQUETS* joueur1, PAQUETS* joueur2) {
    assert(NbLettreRestantAlphabet(Alpha_jeu)>0);
    initVecteur(&joueur1->lettres, NBLETTREJOUEURDEBUT);
    initVecteur(&joueur2->lettres, NBLETTREJOUEURDEBUT);
    for (int i = 0; i < NBLETTREJOUEURDEBUT; i++) {
        char L1 = piochePaquet(Alpha_jeu);
        char L2 = piochePaquet(Alpha_jeu);
        Lettre l1;
        Lettre l2;
        InitLettres(&l1, L1);
        InitLettres(&l2, L2);
        ajouter(&joueur1->lettres, l1);
        ajouter(&joueur2->lettres, l2);
    }
}

void InitPartiedejfait(PAQUETS* joueur1, PAQUETS* joueur2) {
    initVecteur(&joueur1->lettres, NBLETTREJOUEURDEBUT);
    initVecteur(&joueur2->lettres, NBLETTREJOUEURDEBUT);
    for (char i = 'A'; i < NBLETTREJOUEURDEBUT + 'A'; i++) {

        Lettre l1;
        Lettre l2;
        InitLettres(&l1, i);
        InitLettres(&l2, i);
        ajouter(&joueur1->lettres, l1);
        ajouter(&joueur2->lettres, l2);
    }
}

void AfficherPaquetTrie(const PAQUETS* paquet) {
    qsort(paquet->lettres.elements, taille(&paquet->lettres), sizeof(Lettre), comparerLettre);
    for (int i = 0; i < taille(&paquet->lettres); i++) {
        Lettre La = obtenir(&paquet->lettres, i);
        printf("%c",AfficherLettre(&La));
    }
    printf("\n");
}

int comparerLettre(const void* a, const void* b) {
    const Lettre* lettreA = (const Lettre*)a;
    const Lettre* lettreB = (const Lettre*)b;

    // Récupérer les caractères via AfficherLettre
    char charA = AfficherLettre((Lettre*)lettreA);
    char charB = AfficherLettre((Lettre*)lettreB);

    // Comparer les caractères (par leurs valeurs ASCII)
    if (charA < charB) {
        return -1; // lettreA est avant lettreB
    } else if (charA > charB) {
        return 1; // lettreA est après lettreB
    } else {
        return 0; // lettreA est égal à lettreB
    }
}

void EchangePioche(Alphabet* Alpha, char L, PAQUETS* J) {
    printf("\n");
    PlusAlpha(Alpha, L);
    MoinsPaquet(J, L);
    char lettre_ajout = piochePaquet(Alpha);
    PlusPaquet(J, lettre_ajout);
}

int est_dans(const PAQUETS* paquet, const char L) {
    for (int i =0; i < taille(&paquet->lettres);i++) {
        Lettre Le = obtenir(&paquet->lettres, i);
        if (L == AfficherLettre(&Le))
            return 1;
    }
    return 0;
}

void DupliquerPaquet(const PAQUETS* source, PAQUETS* destination) {
    initVecteur(&destination->lettres, NBLETTREJOUEURDEBUT);
    for (int i = 0; i < taille(&source->lettres); i++) {
        Lettre Le = obtenir(&source->lettres, i);
        ajouter(&destination->lettres, Le);
    }
}

void MoinsPaquet(PAQUETS *P, char L) {
    if (est_dans(P, L)) {
        for (int i = 0; i < taille(&P->lettres); i++) {
            Lettre La = obtenir(&P->lettres, i);
            if (AfficherLettre(&La) == L) {
                supprimer(&P->lettres, i);
                break;
            }
        }
    }
}

void PlusPaquet(PAQUETS *P, char L) {
    Lettre lettre;
    InitLettres(&lettre,L);
    ajouter(&P->lettres, lettre);
}

void LibererPaquets(PAQUETS* P) {
    detruireVecteur(&P->lettres);
}

int EstVide(const PAQUETS* P) {
    return (taille(&P->lettres) == 0);
}

int NbRestant(const PAQUETS* P) {
    return taille(&P->lettres);
}