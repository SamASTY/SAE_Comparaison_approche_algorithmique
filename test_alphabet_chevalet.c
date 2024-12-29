#include <stdio.h>

#include "Alphabet.h"
#include "Chevalets.h"
#include "Rail.h"
#include "test_alphabet_chevalet.h"

void test_alphabet() {
    Alphabet Pioche;
    InitAlphabeth(&Pioche);
    PAQUETS J1;
    PAQUETS J2;
    InitPartie(&Pioche, &J1, &J2);
    AfficherPaquettrier(&J1);
    AfficherPaquettrier(&J2);
    AfficherAlphabethCount(&Pioche);
    printf("J1 E %d\n", est_dans(&J1,'E'));
    printf("J2 E %d\n", est_dans(&J2,'E'));
    printf("J1 T %d\n", est_dans(&J1,'T'));
    printf("J2 T %d\n", est_dans(&J2,'T'));
    printf("J1 Q %d\n", est_dans(&J1,'Q'));
    printf("J2 Q %d\n", est_dans(&J2,'Q'));
    PAQUETS J3;
    DupliquerPaquet(&J1,&J3);
    AfficherPaquettrier(&J1);
    AfficherPaquettrier(&J3);
    Rail R_recto;
    Rail R_verso;
    char M1[NBMAXLETTRES] = "ARGI";
    char M2[NBMAXLETTRES] = "BUGF";
    InitRail(&R_recto, M1, M2);
    AfficherRails(&R_recto);
    inverser_rail(&R_recto,&R_verso);
    AfficherRails(&R_verso);

    LibererPaquets(&J1);
    LibererPaquets(&J2);
    LibererAlphabeth(&Pioche);
}
