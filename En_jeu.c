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
        if (est_dans(J, mot_joueur[i]) != 1)
            return 0;
    }
    return 1;
}

int appartient_dans_ordre_rail(Rail* R, char* rail,Sens sens) {
    if (sens == DROITE) {
        int taille_rail = strlen(rail);
        for (int i = taille_rail, j = TAILLERAIL-taille_rail; rail[i] != '\0'; i++ , j--) {
            if (R->lettres[j] != rail[i])
                return 0;
        }
    }
    if (sens == GAUCHE) {
        for (int i =0; rail[i] != '\0'; i++) {
            if (R->lettres[i] != rail[i])
                return 0;
        }
    }
    return 1;
}

void supppresion_chevalets_rail(PAQUETS* J1, char* j1, PAQUETS* J2, char* j2) {
    for (int i = 0; j1[i] != '\0'; i++)
        MoinsPaquet(J1, j1[i]);
    for (int i = 0; j2[i] != '\0'; i++)
        MoinsPaquet(J2, j2[i]);
}

void deplacement_rail_chevalet(PAQUETS* Joueur, char* mot_rail) {
    for (int i = 0; mot_rail[i] != '\0'; i++)
        PlusPaquet(Joueur, mot_rail[i]);
}

void deplacement_chevalet_rail(Rail* R, char* mot_joueur) {
    int a_decaler = strlen(mot_joueur);
    Decalage(R, a_decaler);
    for (int i = 0; mot_joueur[i] != '\0'; i++) {
        R->lettres[i] = mot_joueur[i];
    }
}

void suppresion_lettre_joueur(PAQUETS* J, char* mot_joueur) {
    for (int i = 0; mot_joueur[i] != '\0'; i++)
        MoinsPaquet(J, mot_joueur[i]);
}
