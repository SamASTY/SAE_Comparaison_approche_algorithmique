#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Alphabet.h"

const int letter_count[NBLETTRESALPHABETH] = { ///< Definition du nombre d'apparition de chaque lettre au debut du jeu sous forme de constante
    9,  // A
    1,  // B
    2,  // C
    3,  // D
    14, // E
    1,  // F
    1,  // G
    1,  // H
    7,  // I
    1,  // J
    5,  // L
    3,  // M
    6,  // N
    5,  // O
    2,  // P
    1,  // Q
    6,  // R
    7,  // S
    6,  // T
    5,  // U
    2   // V
};

void InitLettres(Lettre* L, char lettre) {
    L->Lettre[0] = lettre;
    L->Lettre[TAILLEDUNLETTRE-1] = '\0';
}

void InitAlphabeth(Alphabet* Alpha) {
    initVecteur(&Alpha->lettres, NBLETTRESTOTAL);
    int i = 0;
    char j = 'A';
    while (j <= 'V' && i < NBLETTRESALPHABETH) {
        if (j == 'K') {
            // Ignorer 'K'
            j++;
        } else {
            Lettre L;
            InitLettres(&L, j);
            for (int n = 0; n < letter_count[i]; n++) {
                ajouter(&Alpha->lettres, L);
            }
            i++;
            j++;
        }
    }
}

void AfficherAlphabethCount(Alphabet* Alpha) {
    char j = 'A';
    int i = 0;
    while (j<= 'V' && i < NBLETTRESTOTAL+1) {
        if (j == 'K') {
            j++;
            continue;
        }
        printf("%c -> %d\n",j,countLettre(Alpha,j));
        i++;
        j++;
    }
}

void AfficherAlphabeth(Alphabet* Alpha) {
    for (int i = 0; i < taille(&Alpha->lettres); i++) {
        Lettre La = obtenir(&Alpha->lettres, i);
        printf("%c\n",AfficherLettre(&La));
    }

}

int NbLettreRestantAlphabet(const Alphabet* Alpha) {
    return Alpha->lettres.nbElements;
}

char AfficherLettre(Lettre* L) {
    return L->Lettre[0];
}

int est_presente(const Alphabet* Alpha, const char L) {
    for (int i =0; i <taille(&Alpha->lettres);i++) {
        Lettre Le = obtenir(&Alpha->lettres, i);
        if (L == AfficherLettre(&Le)) {
            return 1;
        }
    }
    return 0;
}

int countLettre(const Alphabet* Alpha, char lettre) {
    int compteur = 0;
    if (est_presente(Alpha, lettre)) {
        for (int i = 0; i < taille(&Alpha->lettres); i++){
            Lettre La = (obtenir(&Alpha->lettres, i));
            if (AfficherLettre(&La) == lettre && i < taille(&Alpha->lettres))
                compteur++;
        }
    }
    return compteur;
}

void MoinsAlpha(Alphabet *Alpha, char L) {
    if (est_presente(Alpha, L)) {
        for (int i = 0; i < taille(&Alpha->lettres); i++) {
            Lettre La = obtenir(&Alpha->lettres, i);
            if (AfficherLettre(&La) == L) {
                supprimer(&Alpha->lettres, i);
                break;
            }
        }
    }
}

void PlusAlpha(Alphabet *Alpha, char L) {
    Lettre lettre;
    InitLettres(&lettre,L);
    ajouter(&Alpha->lettres, lettre); // non
}

void LibererAlphabeth(Alphabet* Alpha) {
    detruireVecteur(&Alpha->lettres);
}

