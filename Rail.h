#pragma once


const enum {
    TAILLERAIL = 8, ///< Nombre de lettre maximale pouvant se trouver sur le rail.
    NBMAXLETTRES = 4 ///< Nombre maximal de lettre pouvant être poser par un joueur durant son tour.
};

typedef struct {
    char lettres[TAILLERAIL]; ///< Lettre se trouvant sur le rail.
}Rail;

void InitRail(Rail* rail, char mot1[NBMAXLETTRES], char mot2[NBMAXLETTRES]);

/**
 * @brief Cette fonction permet d'afficher le contenu d'un paquet du debut jusqu'a la fin.
 * @param[in] paquet Paquets que l'on souhaite afficher.
 * @pre Le paquet doit faire partie d'une partie initialiser.
 */
void AfficherRails(Rail* R);

int est_dans_rail(Rail* R, const char L) ;

void inverser_rail(Rail* dans_ordre, Rail* inverser);

void Decalage(Rail *R, int nombredefoie);

void dupliquer_rail_inv(Rail* source, Rail* dest);