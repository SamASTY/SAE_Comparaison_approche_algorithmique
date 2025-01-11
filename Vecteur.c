#include <assert.h>
#include <stdlib.h>

#include "Vecteur.h"

int initVecteur(Vecteur* v, int capacite) {
    assert(capacite > 0);
    v->capacite = capacite;
    v->nbElements = 0;
    v->elements = (Lettre*)malloc(sizeof(Lettre) * capacite);
    return v->elements != NULL;
}

int taille(const Vecteur* v) {
    return v->nbElements;
}

int ajouter(Vecteur* v, Lettre it) {
    const int FACTEUR = 2;
    if (v->nbElements == v->capacite) {
        Lettre* tab = (Lettre*)realloc(v->elements, sizeof(Lettre) * v->capacite * FACTEUR);
        if (tab == NULL)
            return 0;
        v->capacite *= FACTEUR;
        v->elements = tab;
    }
    v->elements[v->nbElements++] = it;
    return 1;
}

Lettre obtenir(const Vecteur* v, int i) {
    assert(i >= 0 && i < v->nbElements);
    return v->elements[i];
}

void modifier(Vecteur* v, int i, Lettre it) {
    assert(i >= 0 && i < v->nbElements);
    v->elements[i] = it;
}

void supprimer(Vecteur* v, int i) {
    assert(i >= 0 && i < v->nbElements);
    for (++i; i < v->nbElements; ++i)
        v->elements[i - 1] = v->elements[i];
    --v->nbElements;
}

int retailler(Vecteur* v, int taille) {
    assert(taille > 0);
    Lettre* tab = (Lettre*)realloc(v->elements, sizeof(Lettre) * taille);
    if (tab == NULL)
        return 0;
    v->elements = tab;
    v->capacite = taille;
    if (v->nbElements > taille)
        v->nbElements = taille;
    return 1;
}

void detruireVecteur(Vecteur* v) {
    free(v->elements);
}

