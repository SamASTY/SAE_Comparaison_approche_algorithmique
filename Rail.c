#include <stdio.h>
#include <string.h>

#include "Rail.h"


void InitRail(Rail *rail, const char mot1[NBMAXLETTRES], const char mot2[NBMAXLETTRES]) {
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

void AfficherRails(const Rail *R) {
    for (int i = 0; i < TAILLERAIL; i++) {
        printf("%c", R->lettres[i]);
    }
    printf("\n");
}

int est_dans_rail(const Rail *R, const char L) {
    for (int i = 0; i < strlen(R->lettres); i++) {
        if (L == R->lettres[i])
            return 1;
    }
    return 0;
}

void inverser_rail(const Rail *dans_ordre, Rail *inverse) {
    for (int i = 0; i < TAILLERAIL; i++) {
        inverse->lettres[TAILLERAIL - i - 1] = dans_ordre->lettres[i];
    }
}

void Decalage(Rail *R, int nombredefois) {
    while (nombredefois > 0) {
        for (int i = TAILLERAIL-1; i > 0; i--) {
            R->lettres[i] = R->lettres[i - 1];
        }
        --nombredefois;
    }
}

void dupliquer_rail_inv(const Rail* source, Rail* dest) {
    for (int i = 0, j = TAILLERAIL-1; i < TAILLERAIL; i++, j--)
        dest->lettres[i] = source->lettres[j];
}
