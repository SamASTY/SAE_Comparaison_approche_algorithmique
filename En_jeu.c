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
    printf("le rail est dans l'ordre\n");
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
}

void sauvegarde_lettre_rail_vers_chevalet(Rail* R, char* mot_joueur, char* lettre_rail) {
    for (int i = 0; mot_joueur[i] != '\0'; i++)
        lettre_rail[i] = R->lettres[i];
}

void deplacement_chevalet_rail(Rail* R, char* mot_joueur, Sens div) {
    if (div == DROITE) {
        inverser_chaine_caractere(mot_joueur);
    }
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

void inverser_chaine_caractere(char* chaine) {
    int longueur = strlen(chaine);
    int i, j;
    char temp;

    for (i = 0, j = longueur - 1; i < j; i++, j--) {
        temp = chaine[i];
        chaine[i] = chaine[j];
        chaine[j] = temp;
    }
}

int coup_joueur_R_V(char* commande, PAQUETS *Joueur, Rail *R_r, Rail *R_v, char* mot) {
    int resultat_coup = 0;
    Sens division = NUL;
    char rail[8] = "", joueur[7] = "";
    division = (commande[2] == '(')
                   ? diviser_droite(commande, rail, joueur, mot)
                   : diviser_gauche(commande, rail, joueur, mot);
    if (division != NUL) {
        if (commande[0] == 'R' && appartient_joueur(Joueur, joueur) &&
            appartient_dans_ordre_rail(R_r, rail, division)
                /*&& est_dans_dico(DICTIONAIRES, mot) == 1 && est_dans_dico(MOTJOUER, mot) == 0*/) {
            ecrire_dans(MOTJOUER, mot);
        } else if (commande[0] == 'V' && appartient_joueur(Joueur, joueur) &&
                   appartient_dans_ordre_rail(R_v, rail, division)
                   /*&& est_dans_dico(DICTIONAIRES, mot) == 1 && est_dans_dico(MOTJOUER, mot) == 0*/) {
            ecrire_dans(MOTJOUER, mot);
        } else {
            return resultat_coup;
        }


        char lettre_rail[TAILLEMAXMOT] = "";
        strcpy(lettre_rail, joueur);
        if ((commande[0] == 'R' && division == GAUCHE)
            || (commande[0] == 'V' && division == DROITE)) {
            sauvegarde_lettre_rail_vers_chevalet(R_v, joueur, lettre_rail);
            deplacement_chevalet_rail(R_r, joueur, division);
            dupliquer_rail_inv(R_r, R_v);
        } else {
            sauvegarde_lettre_rail_vers_chevalet(R_r, joueur, lettre_rail);
            deplacement_chevalet_rail(R_v, joueur, division);
            dupliquer_rail_inv(R_v, R_r);
        }
        ajout_lettre_chevalet(Joueur, lettre_rail);
        suppresion_lettre_joueur(Joueur, joueur);
        resultat_coup = 1;

    }
    return resultat_coup;
}

int coup_joueur_echange_lettre(char* commande, PAQUETS *Joueur, Alphabet* Pioche) {
    int resultat_coup = 0;
    for (int i = 1; i < taille(&Joueur->lettres); i++) {
        Lettre Le = obtenir(&Joueur->lettres, i);
        if (commande[2] == AfficherLettre(&Le)) {
            EchangePioche(Pioche, commande[2], &Joueur);
            resultat_coup++;
            break;
        }
    }
    return resultat_coup;
}

void afficher_etat_jeu(PAQUETS* J1, PAQUETS* J2, Rail* RR, Rail* RV) {
    printf("1 : ");
    AfficherPaquettrier(J1);
    printf("2 : ");
    AfficherPaquettrier(J2);
    printf("R : ");
    AfficherRails(RR);
    printf("V : ");
    AfficherRails(RV);
}

void gererTour(int jeu, PAQUETS* joueur, PAQUETS* joueur_adverse,
    Rail* recto, Rail* verso, Alphabet* pioche,
    PAQUETS* Djoueur,Rail* Drecto, Rail* Dverso ) {
    char commande[TAILLEMAXCOMMANDE];
    int coup = 0, defause = 0;

    while (!coup) {
        if (defause) {
            afficher_etat_jeu(joueur, joueur_adverse, recto, verso);
            printf("-%d >", jeu);
            fgets(commande, sizeof(commande), stdin);
            commande[strcspn(commande, "\n")] = '\0';
            nettoyerTampon();
            MoinsPaquet(joueur, commande[0]);
            (defause)--;
            coup--;
            continue;
        }
        printf("%d >", jeu);
        fgets(commande, sizeof(commande), stdin);
        commande[strcspn(commande, "\n")] = '\0';
        nettoyerTampon();

        if (commande[0] == 'R' || commande[0] == 'V') {
            char mot[9] = "";
            coup = coup_joueur_R_V(commande, joueur, recto, verso, mot);
            if (strlen(mot) == 8 && coup == 1)
                (defause)++;
        } else if (commande[0] == '-' && est_dans(joueur, commande[2])) {
            coup = coup_joueur_echange_lettre(commande, joueur, pioche);
        } else if ((commande[0] == 'r' || commande[0] == 'v')) {
            //coup si l'autre joueur aurai pu posser un mot de 8 lettres.
            // posibilité de defause
        }
    }
}

void nettoyerTampon() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}
