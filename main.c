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

int main() {
    setlocale(LC_ALL, "en_US.UTF-8");
    srand(time(NULL));
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
            } while (lettre_valide(&Joueur1, motjoueur1) == 0 || strlen(motjoueur1) != 4
                /* || est_dans_dico(DICTIONAIRES, motjoueur1) == 0 || est_dans_dico(MOTJOUER, motjoueur1) == 1*/);
            do {
                printf("2 > ");
                scanf("%[^\n]", motjoueur2);
                nettoyerTampon();
            } while (lettre_valide(&Joueur2, motjoueur2) == 0 || strlen(motjoueur2) != 4
                /* || est_dans_dico(DICTIONAIRES, motjoueur2) == 0 || est_dans_dico(MOTJOUER, motjoueur2) == 1*/);
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

        PAQUETS Doublons_J1, Doublons_J2;
        DupliquerPaquet(&Joueur1, &Doublons_J1);
        DupliquerPaquet(&Joueur2, &Doublons_J2);
        Rail R_doublons_R, R_doublons_V;
        char init_doublons[NBMAXLETTRES] = ",,,,";
        InitRail(&R_doublons_R, init_doublons, init_doublons);
        InitRail(&R_doublons_V, init_doublons, init_doublons);
        int partie_principale_jeu = 0;
        int defause1 = 0, defause2 = 0;
        int joueur = 1;
        while (!partie_principale_jeu) {
            afficher_etat_jeu(&Joueur1, &Joueur2, &R_recto, &R_verso);

            DupliquerPaquet(&Joueur1, &Doublons_J1);
            DupliquerPaquet(&Joueur2, &Doublons_J2);
            inverser_rail(&R_recto, &R_doublons_V);
            inverser_rail(&R_verso, &R_doublons_R);

            (joueur == 1
                 ? (gererTour(joueur, &Joueur1, &Joueur2, &R_recto, &R_verso, &Pioche, &Doublons_J2, &R_doublons_R,
                              &R_doublons_V))
                 : (gererTour(joueur, &Joueur2, &Joueur1, &R_recto, &R_verso, &Pioche, &Doublons_J1, &R_doublons_R,
                              &R_doublons_V)
                 )
            );
            (joueur == 1 ? (joueur = 2) : (joueur = 1));
        }
    }
}
