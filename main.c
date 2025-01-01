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

    Rail rail;
    char mot1[]="ouie",mot2[]="none",mot[10],r[]="ouienone";
    InitRail(&rail,mot1,mot2);
    AfficherRails(&rail);
    Sens division = GAUCHE;
    strcpy(mot, "o");
    printf("les lettres %s appartiennent elle au rail a gauche %s\n",mot,appartient_dans_ordre_rail(&rail, mot,division)?"oui":"non");
    strcpy(mot, "ou");
    printf("les lettres %s appartiennent elle au rail a gauche %s\n",mot,appartient_dans_ordre_rail(&rail, mot,division)?"oui":"non");
    strcpy(mot, "oui");
    printf("les lettres %s appartiennent elle au rail a gauche %s\n",mot,appartient_dans_ordre_rail(&rail, mot,division)?"oui":"non");
    strcpy(mot, "ouie");
    printf("les lettres %s appartiennent elle au rail a gauche %s\n",mot,appartient_dans_ordre_rail(&rail, mot,division)?"oui":"non");
    strcpy(mot, "ouien");
    printf("les lettres %s appartiennent elle au rail a gauche %s\n",mot,appartient_dans_ordre_rail(&rail, mot,division)?"oui":"non");
    strcpy(mot, "ouieno");
    printf("les lettres %s appartiennent elle au rail a gauche %s\n",mot,appartient_dans_ordre_rail(&rail, mot,division)?"oui":"non");
    strcpy(mot, "ouienon");
    printf("les lettres %s appartiennent elle au rail a gauche %s\n",mot,appartient_dans_ordre_rail(&rail, mot,division)?"oui":"non");
    strcpy(mot, "ouienone");
    printf("les lettres %s appartiennent elle au rail a gauche %s\n",mot,appartient_dans_ordre_rail(&rail, mot,division)?"oui":"non");
    division = DROITE;
    strcpy(mot, "ouienone");
    printf("les lettres %s appartiennent elle au rail a droite %s\n",mot,appartient_dans_ordre_rail(&rail, mot,division)?"oui":"non");
    strcpy(mot, "uienone");
    printf("les lettres %s appartiennent elle au rail a droite %s\n",mot,appartient_dans_ordre_rail(&rail, mot,division)?"oui":"non");
    strcpy(mot, "ienone");
    printf("les lettres %s appartiennent elle au rail a droite %s\n",mot,appartient_dans_ordre_rail(&rail, mot,division)?"oui":"non");
    strcpy(mot, "enone");
    printf("les lettres %s appartiennent elle au rail a droite %s\n",mot,appartient_dans_ordre_rail(&rail, mot,division)?"oui":"non");
    strcpy(mot, "none");
    printf("les lettres %s appartiennent elle au rail a droite %s\n",mot,appartient_dans_ordre_rail(&rail, mot,division)?"oui":"non");
    strcpy(mot, "one");
    printf("les lettres %s appartiennent elle au rail a droite %s\n",mot,appartient_dans_ordre_rail(&rail, mot,division)?"oui":"non");
    strcpy(mot, "ne");
    printf("les lettres %s appartiennent elle au rail a droite %s\n",mot,appartient_dans_ordre_rail(&rail, mot,division)?"oui":"non");
    strcpy(mot, "e");
    printf("les lettres %s appartiennent elle au rail a droite %s\n",mot,appartient_dans_ordre_rail(&rail, mot,division)?"oui":"non");
    /*
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
                        printf("les lettres appaetiennent elle au joueurs ?%s\n",
                               appartient_joueur(&Joueur1, joueur) ? "oui" : "non");
                        printf("les lettres appaetiennent elle au rail %s\n",
                               appartient_dans_ordre_rail(&R_recto, rail, division) ? "oui" : "non");
                        if (commande[0] == 'R' && appartient_joueur(&Joueur1, joueur) &&
                            appartient_dans_ordre_rail(&R_recto, rail, division)/*
                                && est_dans_dico(DICTIONAIRES, mot) == 0 && est_dans_dico(MOTJOUER, mot) ==1 ) {
                            ecrire_dans(MOTJOUER, mot);
                        } else if (commande[0] == 'V' && appartient_joueur(&Joueur1, joueur) &&
                                   appartient_dans_ordre_rail(&R_verso, rail, division)/*
                            && est_dans_dico(DICTIONAIRES, mot) == 0 && est_dans_dico(MOTJOUER, mot) ==1 ) {
                            ecrire_dans(MOTJOUER, mot);
                        } else {
                            printf("ba nan j'existe pas\n");
                            continue;
                        }


                        char lettre_rail[TAILLEMAXMOT] = "";
                        strcpy(lettre_rail, joueur);
                        if ((commande[0] == 'R' && division == GAUCHE)
                            || (commande[0] == 'V' && division == DROITE)) {
                            sauvegarde_lettre_rail_vers_chevalet(&R_verso, joueur, lettre_rail);
                            deplacement_chevalet_rail(&R_recto, joueur);
                            dupliquer_rail_inv(&R_recto, &R_verso);
                        } else {
                            sauvegarde_lettre_rail_vers_chevalet(&R_recto, joueur, lettre_rail);
                            deplacement_chevalet_rail(&R_verso, joueur);
                            dupliquer_rail_inv(&R_verso, &R_recto);
                        }
                        ajout_lettre_chevalet(&Joueur1, lettre_rail);
                        suppresion_lettre_joueur(&Joueur1, joueur);
                        coupj1++;
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
    */
}
