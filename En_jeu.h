#pragma once

#include "Chevalets.h"
#include "Alphabet.h"
#include "Rail.h"

enum {
    TAILLEMAXCOMMANDE = 13, /// Nombre maximum de caractère pouvant etre fait dans une commande du jeu.
};

typedef enum {NUL,DROITE,GAUCHE}Sens;

int lettre_valide(PAQUETS* joueur, char* mot );

int diviser_gauche(char *com, char *rail, char *joueur, char *mot);

int diviser_droite(char *com, char *rail, char *joueur, char *mot);

void fusion_mot(char* mot, char* p1, char* p2, int taille_p1, int taille_p2);

int appartient_joueur(PAQUETS* J, char* mot_joueur);

int appartient_dans_ordre_rail(Rail* R, char* rail,Sens sens);

void supppresion_chevalets_rail(PAQUETS* J1, char* j1, PAQUETS* J2, char* j2);

void ajout_lettre_chevalet(PAQUETS* Joueur, char* lettre_rail);

void deplacement_chevalet_rail(Rail* R, char* mot_joueur);

void suppresion_lettre_joueur(PAQUETS* J, char* mot_joueur);

void sauvegarde_lettre_rail_vers_chevalet(Rail* R, char* mot_joueur, char* lettre_rail);