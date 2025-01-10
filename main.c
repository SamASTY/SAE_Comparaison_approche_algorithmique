#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "Alphabet.h"
#include "Chevalets.h"
#include "Rail.h"
#include "En_jeu.h"
#include "test.h"
#include "Dictionnaire.h"

enum { MOTPREMIERTOUR = 4};

int main() {
    Dictionnaire dictionnaire;
    Dictionnaire motsDejaJoues;
    motsDejaJoues.mots = NULL;
    motsDejaJoues.nbMots = 0;
    if (!remplirDico(DICTIONNAIRE, &dictionnaire)) {
        fprintf(stderr, "Impossible de remplir le dictionnaire\n");
        return 1;
    }
    test_dictionnaire(&dictionnaire);
    setlocale(LC_ALL, "en_US.UTF-8");
    srand(time(NULL));
    Alphabet Pioche;
    InitAlphabet(&Pioche);
    PAQUETS Joueur1;
    PAQUETS Joueur2;
    InitPartie(&Pioche, &Joueur1, &Joueur2);
    int initialisation = 0;
    char motjoueur1[NBMAXLETTRES + 1];
    char motjoueur2[NBMAXLETTRES + 1];

    while (!initialisation) {
        printf("1 : ");
        AfficherPaquetTrie(&Joueur1);
        printf("2 : ");
        AfficherPaquetTrie(&Joueur2);
        do {
            printf("1 > ");
            scanf("%[^\n]", motjoueur1);
            nettoyerTampon();
        } while (lettre_valide(&Joueur1, motjoueur1) == 0 || strlen(motjoueur1) != MOTPREMIERTOUR
            /* || !est_dans_dico(&dictionnaire, motjoueur1) || est_dans_dico(&motsDejaJoues, motjoueur1)*/);
        do {
            printf("2 > ");
            scanf("%[^\n]", motjoueur2);
            nettoyerTampon();
        } while (lettre_valide(&Joueur2, motjoueur2) == 0 || strlen(motjoueur2) != MOTPREMIERTOUR
             /*|| !est_dans_dico(&dictionnaire, motjoueur2) || est_dans_dico(&motsDejaJoues, motjoueur2)*/);
        initialisation = 1;
        ajouterMotDejaJoue(&motsDejaJoues, motjoueur1);
        ajouterMotDejaJoue(&motsDejaJoues, motjoueur2);
    }
    printf("\n");
    Rail R_recto;
    int joueur_debut = strcmp(motjoueur1, motjoueur2);
    (joueur_debut < 0
         ? InitRail(&R_recto, motjoueur1, motjoueur2)
         : InitRail(&R_recto, motjoueur2, motjoueur1));
    int joueur = (joueur_debut < 0 ? JOUEUR1 : JOUEUR2);
    Rail R_verso;
    inverser_rail(&R_recto, &R_verso);
    ajouterMotDejaJoue(&motsDejaJoues, motjoueur1);
    ajouterMotDejaJoue(&motsDejaJoues, motjoueur2);
    suppression_chevalets_rail(&Joueur1, motjoueur1, &Joueur2, motjoueur2);

    PAQUETS Sauv_J1_n1, Sauv_J1_n2, Sauv_J2_n1, Sauv_J2_n2;
    DupliquerPaquet(&Joueur1, &Sauv_J1_n1);
    DupliquerPaquet(&Joueur2, &Sauv_J2_n1);
    DupliquerPaquet(&Sauv_J1_n1, &Sauv_J1_n2);
    DupliquerPaquet(&Sauv_J2_n1, &Sauv_J2_n2);
    Rail Sauv_RR_n1, Sauv_RR_n2, Sauv_RV_n1, Sauv_RV_n2;

    char init_doublons[NBMAXLETTRES] = ",,,,";
    InitRail(&Sauv_RR_n1, init_doublons, init_doublons);
    InitRail(&Sauv_RV_n1, init_doublons, init_doublons);
    InitRail(&Sauv_RR_n2, init_doublons, init_doublons);
    InitRail(&Sauv_RV_n2, init_doublons, init_doublons);


    int partie_principale_jeu = 0;

    while (!partie_principale_jeu) {

        gestion_sauvegarde(&Joueur1, &Joueur2, &R_recto, &R_verso,
                           &Sauv_J1_n1, &Sauv_J1_n2, &Sauv_J2_n1, &Sauv_J2_n2,
                           &Sauv_RR_n1, &Sauv_RV_n1, &Sauv_RR_n2, &Sauv_RV_n2);
;
        afficher_etat_jeu(&Joueur1, &Joueur2, &R_recto, &R_verso);

        (joueur == JOUEUR1
             ? (gererTour(joueur, &Joueur1, &Joueur2, &R_recto, &R_verso, &Pioche, &Sauv_J2_n2, &Sauv_RR_n2,
                          &Sauv_RV_n2, &dictionnaire, &motsDejaJoues))
             : (gererTour(joueur, &Joueur2, &Joueur1, &R_recto, &R_verso, &Pioche, &Sauv_J1_n2, &Sauv_RR_n2,
                          &Sauv_RV_n2, &dictionnaire, &motsDejaJoues)
             )
        );

        (joueur == JOUEUR1 ? (joueur = JOUEUR2) : (joueur = JOUEUR1));

        if (jeu_fini(&Joueur1, &Joueur2))
            partie_principale_jeu++;
    }
    LibererPaquets(&Joueur1);
    LibererPaquets(&Joueur1);
    LibererAlphabet(&Pioche);
    LibererDico(&dictionnaire);
    LibererDico(&motsDejaJoues);
}
