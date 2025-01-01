#include "Rail.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Rail.h"
#include "Chevalets.h"
#include "Alphabet.h"
#include "Rail.h"
#include "Dictionaire.h"
#include"En_jeu.h"

int lettre_valide(PAQUETS *joueur, char *mot) {
    PAQUETS Joueurdup;
    DupliquerPaquet(joueur, &Joueurdup);
    for (int i = 0; mot[i] != '\0'; i++) {
        int appartient = (est_dans(&Joueurdup, mot[i]));
        if (appartient == 0) {
            LibererPaquets(&Joueurdup);
            return 0;
        }
        if (appartient == 1)
            MoinsPaquet(&Joueurdup, mot[i]);
    }
    LibererPaquets(&Joueurdup);
    return 1;
}

void fusion_mot(char *mot, char *p1, char *p2, int taille_p1, int taille_p2) {
    int it = 0;
    for (int m = 0; m < taille_p1; m++) {
        mot[it] = p1[m];
        it++;
    }
    for (int m = 0; m < taille_p2; m++) {
        mot[it] = p2[m];
        it++;
    }
    mot[it] = '\0';
}

int diviser_gauche(char *com, char *rail, char *joueur, char *mot) {
    int taille_rail = 0, taille_joueur = 0;
    int i = 2;

    while (com[i] != '(' && com[i] != '\0') {
        joueur[taille_joueur] = com[i];


        taille_joueur++;
        i++;
    }
    joueur[taille_joueur] = '\0';

    if (com[i] != '(')
        return NUL;
    i++;

    while (com[i] != ')' && com[i] != '\0') {
        rail[taille_rail] = com[i];


        taille_rail++;
        i++;
    }
    rail[taille_rail] = '\0';

    if (com[i] != ')')
        return NUL;

    fusion_mot(mot, joueur, rail, taille_joueur, taille_rail);
    return GAUCHE;
}

int diviser_droite(char *com, char *rail, char *joueur, char *mot) {
    int taille_rail = 0, taille_joueur = 0;
    int i = 2;
    if (com[i] != '(')
        return NUL;
    i++;

    while (com[i] != ')' && com[i] != '\0') {
        rail[taille_rail] = com[i];
        taille_rail++;
        i++;
    }

    rail[taille_rail] = '\0';

    if (com[i] != ')')
        return NUL;
    i++;


    while (com[i] != '\0') {
        joueur[taille_joueur] = com[i];
        taille_joueur++;
        i++;
    }
    joueur[taille_joueur] = '\0';

    fusion_mot(mot, rail,joueur , taille_rail, taille_joueur);
    return DROITE;
}

int appartient_joueur(PAQUETS* J, char* mot_joueur) {
    for (int i = 0; mot_joueur[i] != '\0'; i++) {
        if (est_dans(J, mot_joueur[i]) == 0)
            return 0;
    }
    return 1;
}


int appartient_dans_ordre_rail(Rail* R, char* mot, Sens sens) {
    int i, j;
    int taille_rail = strlen(R->lettres);
    int taille_mot = strlen(mot);

    if (sens == GAUCHE) {
        for (i = 0; i <= taille_rail - taille_mot; i++) {
            for (j = 0; j <= taille_mot; j++) {
                if (strncmp(R->lettres + i, mot, j) == 0) {
                    return 1;
                }
            }
        }
    }

    if (sens == DROITE) {
        for (i = taille_rail - 1; i >= taille_mot - 1; i--) {
            for (j = 0; j <= taille_mot; j++) {
                if (strncmp(R->lettres + i - j, mot, j) == 0) {
                    return 1;
                }
            }
        }
    }

    return 0;
}


void supppresion_chevalets_rail(PAQUETS* J1, char* j1, PAQUETS* J2, char* j2) {
    for (int i = 0; j1[i] != '\0'; i++)
        MoinsPaquet(J1, j1[i]);
    for (int i = 0; j2[i] != '\0'; i++)
        MoinsPaquet(J2, j2[i]);
}

void ajout_lettre_chevalet(PAQUETS* Joueur, char* lettre_rail) {
    for (int i = 0; lettre_rail[i] != '\0'; i++)
        PlusPaquet(Joueur, lettre_rail[i]);
    printf("les cartes des rails sont dans le paquets :");
    AfficherPaquettrier(Joueur);
}

void sauvegarde_lettre_rail_vers_chevalet(Rail* R, char* mot_joueur, char* lettre_rail) {
    for (int i = 0; mot_joueur[i] != '\0'; i++)
        lettre_rail[i] = R->lettres[i];
}

void deplacement_chevalet_rail(Rail* R, char* mot_joueur) {
    int a_decaler = strlen(mot_joueur);
    Decalage(R, a_decaler);
    printf("le rails est decaler :");
    AfficherRails(R);
    for (int i = 0; mot_joueur[i] != '\0'; i++) {
        R->lettres[i] = mot_joueur[i];
    }
    printf("le rails est a jour avec les lettres du joueurs :");
    AfficherRails(R);
}

void suppresion_lettre_joueur(PAQUETS* J, char* mot_joueur) {
    for (int i = 0; mot_joueur[i] != '\0'; i++)
        MoinsPaquet(J, mot_joueur[i]);
    printf("Lettre utiliser par le joueur supprimer du paquets: ");
    AfficherPaquettrier(J);
}

