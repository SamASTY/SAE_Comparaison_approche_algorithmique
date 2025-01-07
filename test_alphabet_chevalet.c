#include <stdio.h>

#include "Alphabet.h"
#include "Chevalets.h"
#include "Rail.h"
#include "test_alphabet_chevalet.h"

#include <assert.h>

void test_distribution_paquets() {
    Alphabet Pioche;
    InitAlphabet(&Pioche);
    PAQUETS J1;
    PAQUETS J2;
    InitPartie(&Pioche, &J1, &J2);
    AfficherPaquetTrie(&J1);
    AfficherPaquetTrie(&J2);
    AfficherAlphabetCount(&Pioche);
    printf("J1 -> E %s\n", est_dans(&J1,'E')?"oui":"non");
    printf("J2 -> E %s\n", est_dans(&J2,'E')?"oui":"non");
    printf("J1 -> T %s\n", est_dans(&J1,'T')?"oui":"non");
    printf("J2 -> T %s\n", est_dans(&J2,'T')?"oui":"non");
    printf("J1 -> Q %s\n", est_dans(&J1,'Q')?"oui":"non");
    printf("J2 -> Q %s\n", est_dans(&J2,'Q')?"oui":"non");
    PAQUETS J3;
    DupliquerPaquet(&J1,&J3);
    AfficherPaquetTrie(&J1);
    AfficherPaquetTrie(&J3);

    LibererPaquets(&J1);
    LibererPaquets(&J2);
    LibererAlphabeth(&Pioche);
}

void test_utilisation_paquets() {
    Alphabet Pioche;
    InitAlphabet(&Pioche);
    PAQUETS Joueur1;
    PAQUETS Joueur2;
    InitPartiedejfait(&Joueur1, &Joueur2);
    AfficherAlphabet(&Pioche);
    printf("J1 :");
    AfficherPaquetTrie(&Joueur1);
    printf("J2 :");
    AfficherPaquetTrie(&Joueur2);
    MoinsPaquet(&Joueur1,'A');
    assert(est_dans(&Joueur1,'A')==0);
    printf("J1 :");
    AfficherPaquetTrie(&Joueur1);
    PlusPaquet(&Joueur1,'M');
    assert(est_dans(&Joueur1,'M')==1);
    printf("J1 :");
    AfficherPaquetTrie(&Joueur1);
    MoinsPaquet(&Joueur2,'A');
    MoinsPaquet(&Joueur2,'B');
    MoinsPaquet(&Joueur2,'C');
    MoinsPaquet(&Joueur2,'D');
    MoinsPaquet(&Joueur2,'E');
    MoinsPaquet(&Joueur2,'F');
    MoinsPaquet(&Joueur2,'G');
    MoinsPaquet(&Joueur2,'H');
    MoinsPaquet(&Joueur2,'I');
    MoinsPaquet(&Joueur2,'J');
    MoinsPaquet(&Joueur2,'K');
    MoinsPaquet(&Joueur2,'L');
    assert(EstVide(&Joueur2)==1);
    printf("J2 :");
    AfficherPaquetTrie(&Joueur2);
}

void test_creation_rail() {
    Rail R_recto;
    Rail R_verso;
    char M1[NBMAXLETTRES] = "BLEU";
    char M2[NBMAXLETTRES] = "JAUN";
    InitRail(&R_recto, M1, M2);
    AfficherRails(&R_recto);
    inverser_rail(&R_recto,&R_verso);
    AfficherRails(&R_verso);
}