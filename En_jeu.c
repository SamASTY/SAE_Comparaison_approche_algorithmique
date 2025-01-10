#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Chevalets.h"
#include "Alphabet.h"
#include "Dictionnaire.h"
#include"En_jeu.h"
#include "Rail.h"


int lettre_valide(const PAQUETS *joueur, const char *mot) {
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

void fusion_mot(char *mot, const char *p1, const char *p2, int taille_p1, int taille_p2) {
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

int diviser_gauche(const char *com, char *rail, char *joueur, char *mot) {
    int taille_rail = 0, taille_joueur = 0;
    int i = DEBUTLETTRES;

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

int diviser_droite(const char *com, char *rail, char *joueur, char *mot) {
    int taille_rail = 0, taille_joueur = 0;
    int i = DEBUTLETTRES;
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

    fusion_mot(mot, rail, joueur, taille_rail, taille_joueur);
    return DROITE;
}

int appartient_joueur(const PAQUETS *J, const char *mot_joueur) {
    for (int i = 0; mot_joueur[i] != '\0'; i++) {
        if (est_dans(J, mot_joueur[i]) == 0)
            return 0;
    }
    return 1;
}

int appartient_dans_ordre_rail(const Rail *R, const char *mot, const Sens sens) {
    int i, j;
    int taille_rail = (int) strlen(R->lettres);
    int taille_mot = (int) strlen(mot);

    if (sens == GAUCHE) {
        for (i = 0; i <= taille_rail - taille_mot; i++) {
            int trouve = 1;
            for (j = 0; j < taille_mot; j++) {
                if (R->lettres[i + j] != mot[j]) {
                    trouve = 0;
                    break;
                }
            }
            if (trouve) {
                return 1;
            }
        }
    }

    if (sens == DROITE) {
        for (i = taille_rail - 1; i >= taille_mot - 1; i--) {
            int trouve = 1;
            for (j = 0; j < taille_mot; j++) {
                if (R->lettres[i - j] != mot[taille_mot - 1 - j]) {
                    trouve = 0;
                    break;
                }
            }
            if (trouve) {
                return 1;
            }
        }
    }

    return 0; // Mot non trouvé
}

void suppression_chevalets_rail(PAQUETS *J1, const char *j1, PAQUETS *J2, const char *j2) {
    for (int i = 0; j1[i] != '\0'; i++)
        MoinsPaquet(J1, j1[i]);
    for (int i = 0; j2[i] != '\0'; i++)
        MoinsPaquet(J2, j2[i]);
}

void ajout_lettre_chevalet(PAQUETS *Joueur, const char *lettre_rail) {
    for (int i = 0; lettre_rail[i] != '\0'; i++)
        PlusPaquet(Joueur, lettre_rail[i]);
}

void sauvegarde_lettre_rail_vers_chevalet(const Rail *R, const char *mot_joueur, char *lettre_rail) {
    for (int i = 0; mot_joueur[i] != '\0'; i++)
        lettre_rail[i] = R->lettres[i];
}

void deplacement_chevalet_rail(Rail *R, char *mot_joueur, const Sens div) {
    if (div == DROITE) {
        inverser_chaine_caractere(mot_joueur);
    }
    int a_decaler = (int) strlen(mot_joueur);
    Decalage(R, a_decaler);
    for (int i = 0; mot_joueur[i] != '\0'; i++) {
        R->lettres[i] = mot_joueur[i];
    }
}

void suppression_lettre_joueur(PAQUETS *J, const char *mot_joueur) {
    for (int i = 0; mot_joueur[i] != '\0'; i++)
        MoinsPaquet(J, mot_joueur[i]);
}

void inverser_chaine_caractere(char *chaine) {
    int longueur = (int) strlen(chaine);
    int i, j;
    char temp;

    for (i = 0, j = longueur - 1; i < j; i++, j--) {
        temp = chaine[i];
        chaine[i] = chaine[j];
        chaine[j] = temp;
    }
}

int coup_joueur_R_V(const char *commande, PAQUETS *Joueur, PAQUETS *Adversaire, Rail *R_r, Rail *R_v, char *mot, const Dictionnaire* dictionnaire, Dictionnaire* motsDejaJoues) {
    int resultat_coup = 0;
    Sens division = NUL;
    char rail[TAILLERAIL] = "", joueur[TAILLERAIL - 1] = "";
    division = (commande[DEBUTLETTRES] == '(')
                   ? diviser_droite(commande, rail, joueur, mot)
                   : diviser_gauche(commande, rail, joueur, mot);
    if (division != NUL) {
        if ((commande[0] == 'R' || commande[0] == 'r') && appartient_joueur(Joueur, joueur) &&
            appartient_dans_ordre_rail(R_r, rail, division)
            /*&& est_dans_dico(dictionnaire, mot) && !est_dans_dico(motsDejaJoues, mot)*/) {
            ajouterMotDejaJoue(motsDejaJoues, mot);
        } else if ((commande[0] == 'V' || commande[0] == 'v') && appartient_joueur(Joueur, joueur) &&
                   appartient_dans_ordre_rail(R_v, rail, division)
            /*&& est_dans_dico(dictionnaire, mot) && !est_dans_dico(motsDejaJoues, mot)*/) {
            ajouterMotDejaJoue(motsDejaJoues, mot);
        } else {
            return resultat_coup;
        }
        resultat_coup = 1;
        if (commande[0] == 'R' || commande[0] == 'V') {
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
            ajout_lettre_chevalet(Adversaire, lettre_rail);
            suppression_lettre_joueur(Joueur, joueur);
        }
    }
    return resultat_coup;
}

int coup_joueur_echange_lettre(const char *commande, PAQUETS *Joueur, Alphabet *Pioche) {
    int resultat_coup = 0;
    for (int i = 0; i < taille(&Joueur->lettres); i++) {
        Lettre Le = obtenir(&Joueur->lettres, i);
        if (commande[DEBUTLETTRES] == AfficherLettre(&Le)) {
            EchangePioche(Pioche, commande[DEBUTLETTRES], Joueur);
            resultat_coup++;
            break;
        }
    }
    return resultat_coup;
}

void afficher_etat_jeu(const PAQUETS *J1, const PAQUETS *J2, const Rail *RR, const Rail *RV) {
    printf("1 : ");
    AfficherPaquetTrie(J1);
    printf("2 : ");
    AfficherPaquetTrie(J2);
    printf("R : ");
    AfficherRails(RR);
    printf("V : ");
    AfficherRails(RV);
    printf("\n");
}

void gererTour(JOUEUR jeu, PAQUETS *joueur, PAQUETS *joueur_adverse,
    Rail *recto, Rail *verso, Alphabet *pioche,
    PAQUETS *Djoueur_adverse, Rail *Drecto, Rail *Dverso,
    const Dictionnaire* dictionnaire, Dictionnaire* motsDejaJoues) {
        char premcommande[TAILLEMAXCOMMANDE];
    char commande[TAILLEMAXCOMMANDE];
    int coup = 0;

    while (!coup) {
        printf("%d >", jeu);
        lireCommande(premcommande,commande, sizeof(commande));
        if (commande[0] == 'R' || commande[0] == 'V') {
            char mot[TAILLEMAXMOT + 1] = "";
            coup = coup_joueur_R_V(commande, joueur, joueur_adverse, recto, verso, mot, dictionnaire, motsDejaJoues);
            if (strlen(mot) == TAILLEMAXMOT && coup == 1 && NbRestant(joueur) > 0) {
                if (jeu == JOUEUR1) {
                    afficher_etat_jeu(joueur, joueur_adverse, recto, verso);
                } else {
                    afficher_etat_jeu(joueur_adverse, joueur, recto, verso);
                }
                defausse_lettre(jeu, joueur);
            }
        } else if (commande[0] == '-' && est_dans(joueur, commande[DEBUTLETTRES])) {
            coup = coup_joueur_echange_lettre(commande, joueur, pioche);
        } else if ((commande[0] == 'r' || commande[0] == 'v') && Drecto->lettres[0] != ',' && !strcmp(recto,Drecto)) {
            char mot[TAILLEMAXMOT + 1] = "";
            coup = coup_joueur_R_V(commande, Djoueur_adverse, joueur, Drecto, Dverso, mot, dictionnaire, motsDejaJoues);
            if (strlen(mot) == TAILLEMAXMOT && coup == 1)
                defausse_lettre(jeu, joueur);
        }
    }
}

void nettoyerTampon() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void lireCommande(char *commande,char vrai_commande[TAILLEMAXCOMMANDE], const size_t taille) {
    if (fgets(commande, (int) taille, stdin) != NULL) {
        commande[strcspn(commande, "\n")] = '\0'; // Supprime le '\n' s'il existe
    } else {
        commande[0] = '\0'; // Vide la chaîne en cas d'erreur
    }
    fflush(stdin);
    ;
    suppression_espace_commande(commande, vrai_commande);
}

void suppression_espace_commande(const char* commande, char* vrai_commande) {
    int i = DEBUTLETTRES, j = DEBUTLETTRES;

    vrai_commande[0] = commande[0];
    vrai_commande[1] = ' ';

    while (commande[i] == ' ') {
        i++;
    }

    while (commande[i] != '\0' && j < TAILLEMAXCOMMANDE - 1) {
        vrai_commande[j++] = commande[i++];
    }

    vrai_commande[j] = '\0';
}

void defausse_lettre(const JOUEUR joueur, PAQUETS *Joueur) {
    char premcommande[TAILLEMAXCOMMANDE] = ",";
    char commande[TAILLEMAXCOMMANDE] = ",";
    while (est_dans(Joueur, commande[0]) == 0) {
        printf("-%d >", joueur);
        lireCommande(premcommande, commande, sizeof(commande));
    }
    MoinsPaquet(Joueur, commande[0]);
}

void gestion_sauvegarde(const PAQUETS *Joueur1, const PAQUETS *Joueur2, const Rail *R_recto, const Rail *R_verso,
                        PAQUETS *Sauv_J1_n1, PAQUETS *Sauv_J1_n2, PAQUETS *Sauv_J2_n1, PAQUETS *Sauv_J2_n2,
                        Rail *Sauv_RR_n1, Rail *Sauv_RV_n1, Rail *Sauv_RR_n2, Rail *Sauv_RV_n2) {
    DupliquerPaquet(Sauv_J1_n1, Sauv_J1_n2);
    DupliquerPaquet(Sauv_J2_n1, Sauv_J2_n2);
    inverser_rail(Sauv_RR_n1, Sauv_RV_n2);
    inverser_rail(Sauv_RV_n1, Sauv_RR_n2);

    DupliquerPaquet(Joueur1, Sauv_J1_n1);
    DupliquerPaquet(Joueur2, Sauv_J2_n1);
    inverser_rail(R_recto, Sauv_RV_n1);
    inverser_rail(R_verso, Sauv_RR_n1);
}


int jeu_fini(const PAQUETS *J1, const PAQUETS *J2) {
    return (EstVide(J1) || EstVide(J2));
}
