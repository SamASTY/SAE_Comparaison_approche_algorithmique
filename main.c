#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <threads.h>
#include <time.h>

#include "Alphabet.h"
#include "Chevalets.h"
#include "Rail.h"
#include "En_jeu.h"
#include "test_alphabet_chevalet.h"
#include "Dictionaire.h"

void nettoyerTampon() {
    // Nettoyage du tampon d'entrée pour éviter les caractères résiduels
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

int main() {
    setlocale(LC_ALL, "en_US.UTF-8");
    srand(time(NULL));
    //test_alphabet();

    int jeu_en_cour = 0;
    while (!jeu_en_cour) {
        effaser_fichier(MOTJOUER);
        Alphabet Pioche;
        InitAlphabeth(&Pioche);
        PAQUETS Joueur1;
        PAQUETS Joueur2;
        InitPartie(&Pioche, &Joueur1, &Joueur2);
        int partie_en_cour = 0;
        int initialisation = 0;
        while (!partie_en_cour) {
            char motjoueur1[NBMAXLETTRES + 1];
            char motjoueur2[NBMAXLETTRES + 1];

            while (!initialisation) {
                printf("1 : ");
                AfficherPaquettrier(&Joueur1);
                printf("2 : ");
                AfficherPaquettrier(&Joueur2);
                do {
                    printf("1 > ");
                    scanf("%[^\n]", motjoueur1);
                    nettoyerTampon();
                } while (lettre_valide(&Joueur1, motjoueur1) == 0 || strlen(motjoueur1) != 4 || est_dans_dico(
                             DICTIONAIRES, motjoueur1) == 1);
                do {
                    printf("2 > ");
                    scanf("%[^\n]", motjoueur2);
                    nettoyerTampon();
                } while (lettre_valide(&Joueur2, motjoueur2) == 0 || strlen(motjoueur2) != 4 || est_dans_dico(
                             DICTIONAIRES, motjoueur2) == 1);
                initialisation = 1;
            }

            printf("\n");
            Rail R_recto;
            (strcmp(motjoueur1, motjoueur2) < 0
                 ? InitRail(&R_recto, motjoueur1, motjoueur2)
                 : InitRail(&R_recto, motjoueur2, motjoueur1));
            Rail R_verso;
            inverser_rail(&R_recto, &R_verso);

            ecrire_dans(MOTJOUER, motjoueur1);
            ecrire_dans(MOTJOUER, motjoueur2);
            supppresion_chevalets_rail(&Joueur1, motjoueur1, &Joueur2, motjoueur2);

            int partie_principale = 0;
            while (!partie_principale) {
                printf("1 : ");
                AfficherPaquettrier(&Joueur1);
                printf("2 : ");
                AfficherPaquettrier(&Joueur2);

                printf("R : ");
                AfficherRails(&R_recto);
                printf("V : ");
                AfficherRails(&R_verso);

                partie_en_cour = 1;
                jeu_en_cour = 1;

                char commande[TAILLEMAXCOMMANDE];
                int coupj1 = 0, defause1 = 0, coupj2 = 0, defause2 = 0;
                while (!coupj1) {
                    printf("1 >");
                    fgets(commande, sizeof(commande), stdin);
                    commande[strcspn(commande, "\n")] = '\0';
                    nettoyerTampon();
                    if (defause1) {
                        // proposer de defauser une lettre si le mot precedent etais de 8 lettres
                        continue;
                    }
                    if (commande[0] == 'R' || commande[0] == 'V') {
                        Sens division = NUL;
                        char mot[9] = "", rail[8] = "", joueur[7] = "";
                        division = (commande[2] == '(')
                                       ? diviser_droite(commande, rail, joueur, mot)
                                       : diviser_gauche(commande, rail, joueur, mot);
                        printf("sens -> %d\n", division);
                        if (division != NUL) {
                            if (commande[0] == 'R' && appartient_joueur(&Joueur1, joueur) && appartient_dans_ordre_rail(
                                    &R_recto, rail,
                                    division) && est_dans_dico(DICTIONAIRES, mot) == 0 && est_dans_dico(MOTJOUER, mot)
                                ==
                                1) {
                                ecrire_dans(MOTJOUER, mot);
                            }
                            if (commande[0] == 'V' && appartient_joueur(&Joueur1, joueur) && appartient_dans_ordre_rail(
                                    &R_verso, rail,
                                    division) && est_dans_dico(DICTIONAIRES, mot) == 0 && est_dans_dico(MOTJOUER, mot)
                                ==
                                1) {
                                ecrire_dans(MOTJOUER, mot);
                            }
                        }
                        else
                            continue;
                        deplacement_rail_chevalet(&Joueur1, rail);
                        if ((commande[0] == 'R' && division == GAUCHE)
                            || (commande[0] == 'V' && division == DROITE)) {
                            deplacement_chevalet_rail(&R_recto, joueur);
                            dupliquer_rail_inv(&R_verso,&R_recto);
                        } else {
                            deplacement_chevalet_rail(&R_verso, joueur);
                            dupliquer_rail_inv(&R_recto,&R_verso);
                        }
                        suppresion_lettre_joueur(&Joueur1, motjoueur1);
                        coupj1++;
                        // il manque l'echange des lettres
                        // si le mot est de 8 lettres alors
                    }
                    if (commande[0] == '-' && est_dans(&Joueur1, commande[2])) {
                        for (int i = 1; i < taille(&Joueur1.lettres); i++) {
                            Lettre Le = obtenir(&Joueur1.lettres, i);
                            if (commande[2] == AfficherLettre(&Le)) {
                                EchangePioche(&Pioche, &Le);
                                coupj1++;
                                break;
                            }
                        }
                    }
                    if ((commande[0] == 'r' || commande[0] == 'v')) {
                        //coup si l'autre joueur aurai pu posser un mot de 8 lettres.
                        // posibilité de defause
                    }
                }
            }
        }
    }
}
