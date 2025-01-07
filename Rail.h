#pragma once


const enum {
    TAILLERAIL = 8,  ///< Nombre de lettres maximal pouvant se trouver sur le rail.
    NBMAXLETTRES = 4 ///< Nombre maximal de lettres pouvant être posées par un·e joueur·se durant son tour.
};

typedef struct {
    char lettres[TAILLERAIL]; ///< Lettre se trouvant sur le rail.
}Rail;

/**
 * @brief Initialise le rail
 * @param[out] rail le rail à initialiser
 * @param[in] mot1 le premier mot déposé sur le rail
 * @param[in] mot2 le deuxième mot déposé sur le rail
 */
void InitRail(Rail* rail, const char mot1[NBMAXLETTRES], const char mot2[NBMAXLETTRES]);

/**
 * @brief Affiche le contenu d'un rail
 * @param[in] R L'adresse du rail à afficher
 * @pre Le rail doit faire partie d'une partie initialisée
 */
void AfficherRails(const Rail* R);

/**
 * @brief Détermine si une lettre est présente sur le rail
 * @param[in] R Le rail en question
 * @param[in] L La lettre dont on cherche à vérifier la présence
 * @return Vrai si la lettre se situe dans le rail, faux sinon
 */
int est_dans_rail(const Rail* R, const char L) ;

/**
 * @brief Inverse un rail
 * @param[in] dans_ordre Le rail initial à inverser
 * @param[out] inverse Le rail qui contiendra le rail initial inversé
 */
void inverser_rail(const Rail* dans_ordre, Rail* inverse);

/**
 * @brief Décale les lettres sur le rail un certain nombre de fois
 * @param[in, out] R Le rail en question
 * @param[in] nombredefoie Le nombre de fois qu'il faut décaler les lettres
 */
void Decalage(Rail *R, int nombredefoie);

/**
 * @brief Duplique un rail
 * @param[in] source Le rail source à dupliquer
 * @param[out] dest Le rail destinataire où dupliquer le rail source
 */
void dupliquer_rail_inv(const Rail* source, Rail* dest);