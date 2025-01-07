#include <stdio.h>
#include <string.h>


#include "Rail.h"


void InitRail(Rail *rail, char mot1[NBMAXLETTRES], char mot2[NBMAXLETTRES]) {
    int compteur = 0;
    for (int i = 0; i < NBMAXLETTRES; i++) {
        rail->lettres[compteur] = mot1[i];
        ++compteur;
    }
    for (int i = 0; i < NBMAXLETTRES && compteur < TAILLERAIL; i++) {
        rail->lettres[compteur] = mot2[i];
        ++compteur;
    }
}

void AfficherRails(Rail *R) {
    for (int i = 0; i < TAILLERAIL; i++) {
        printf("%c,", R->lettres[i]);
    }
    printf("\n");
}

int est_dans_rail(Rail *R, const char L) {
    for (int i = 0; i < strlen(R->lettres); i++) {
        if (L == R->lettres[i])
            return 1;
    }
    return 0;
}

void inverser_rail(Rail *dans_ordre, Rail *inverser) {
    for (int i = 0; i < TAILLERAIL; i++) {
        inverser->lettres[TAILLERAIL - i - 1] = dans_ordre->lettres[i];
    }
}

void Decalage(Rail *R, int nombredefoie) {
    while (nombredefoie > 0) {
        for (int i = TAILLERAIL-1; i > 0; i--) {
            R->lettres[i] = R->lettres[i - 1];
        }
        --nombredefoie;
    }
}

void dupliquer_rail_inv(Rail* source, Rail* dest) {
    for (int i = 0, j = TAILLERAIL-1; i < TAILLERAIL; i++, j--)
        dest->lettres[i] = source->lettres[j];
}
