#pragma once

#include "Chevalets.h"
#include "Alphabet.h"
#include "Rail.h"
#include "Dictionnaire.h"

enum {
    TAILLEMAXCOMMANDE = 50, /// Nombre maximum de caractères pouvant être fait dans une commande du jeu.
    DEBUTLETTRES = 2 /// Debut de commandes autres que celle de défausse de lettres.
};


typedef enum {JOUEUR1 = 1, JOUEUR2}JOUEUR; ///Joueur·ses du jeu

typedef enum {NUL,DROITE,GAUCHE}Sens;

/**
 * @brief Vérifie que les lettres d'un mot se situent bien toutes dans le paquet d'un joueur
 * @param[in] joueur L'adresse du paquet d'un·e joueur·se
 * @param[in] mot Le mot saisi par le/la joueur·se
 * @return Vrai si les lettres du mot sont valides, faux sinon.
 */
int lettre_valide(const PAQUETS* joueur, const char* mot );

/**
* @brief Divise le coup joué par le/la joueur·se s'il est inséré à gauche du rail tout en vérifiant qu'il respecte la syntaxe.
* @param[in] com Commande du/de la joueur·se.
* @param[out] rail Partie de la commande contenant le rail.
* @param[out] joueur Partie de la commande comportant les lettres du/de la joueur·se.
* @param[out] mot Mot créé durant le coup du/de la joueur·se.
* return Renvoie le sens d'insertion si le mot est valide, sinon renvoie une erreur au programme.
*/
int diviser_gauche(const char *com, char *rail, char *joueur, char *mot);

/**
* @brief Divise le coup joué par le/la joueur·se s'il est inséré à droite du rail tout en vérifiant qu'il respecte la syntaxe.
* @param[in] com Commande du/de la joueur·se.
* @param[out] rail Partie de la commande contenant le rail.
* @param[out] joueur Partie de la commande comportant les lettres du joueur.
* @param[out] mot Mot créé durant le coup du/de la joueur·se.
* return Renvoie le sens d'insertion si le mot est valide, sinon renvoie une erreur au programme.
*/
int diviser_droite(const char *com, char *rail, char *joueur, char *mot);

/**
* @brief Fusionne deux chaînes de caractères en une seule pour créer un mot.
* @param[out] mot Mot formé par la fusion des deux autres.
* @param[in] p1 Première chaîne de caractères.
* @param[in] p2 Seconde chaîne de caractères.
* @param[in] taille_p1 Taille de la première chaîne de caractères.
* @param[in] taille_p2 Taille de la seconde chaîne de caractères.
*/
void fusion_mot(char* mot, const char* p1, const char* p2, int taille_p1, int taille_p2);

/**
 * @brief Vérifie si un mot appartient au paquet d'un·e joueur·se
 * @param[in] J L'adresse du paquet du/de la joueur·se
 * @param mot_joueur Le mot saisi par le/la joueur·se
 * @return Vrai si le mot appartient au paquet, faux sinon
 */
int appartient_joueur(const PAQUETS* J, const char* mot_joueur);

/**
 * @brief Vérifie qu'un mot est formé avec le rail dans un sens ou dans l'autre
 * @param[in] R L'adresse du rail
 * @param[in] rail Le mot saisi
 * @param[in] sens Le sens du rail
 * @return vrai si le mot est formé, faux sinon
 */
int appartient_dans_ordre_rail(const Rail* R, const char* rail, const Sens sens);

/**
 * @brief Supprime des lettres contenues dans des mots de paquets donnés
 * @param[in,out] J1 L'adresse du paquet duquel retirer le premier mot
 * @param[in] j1 Le premier mot
 * @param[in,out] J2 L'adresse du paquet duquel retirer le second mot
 * @param[in] j2 Le second mot
 */
void suppression_chevalets_rail(PAQUETS* J1, const char* j1, PAQUETS* J2, const char* j2);

/**
 * @brief Ajoute une lettre à un paquet
 * @param[out] Joueur L'adresse du paquet auquel rajouter la lettre
 * @param[in] lettre_rail La lettre à ajouter
 */
void ajout_lettre_chevalet(PAQUETS* Joueur, const char* lettre_rail);

/**
 * @brief Décale les chevalets du rail pour y ajouter le mot d'un·e joueur·se
 * @param[out] R L'adresse du rail
 * @param[in] mot_joueur Le mot du/de la joueur·se
 * @param[in] div Le sens du rail pour lequel ajouter le mot
 */
void deplacement_chevalet_rail(Rail* R, char* mot_joueur, const Sens div);

/**
 * @brief Supprime les lettres d'un mot d'un paquet d'un·e joueur·se
 * @param[out] J Le paquet duquel retirer les lettres
 * @param[in] mot_joueur Le mot à retirer
 */
void suppression_lettre_joueur(PAQUETS* J, const char* mot_joueur);

/**
 * @brief Recopie n lettres d'un rail dans un tableau de char
 * @param[in] R L'adresse du rail duquel recopier les lettres
 * @param[in] mot_joueur Le mot dont la longueur détermine le nombre de lettres à recopier
 * @param[out] lettre_rail La chaîne de caractères où recopier les lettres
 */
void sauvegarde_lettre_rail_vers_chevalet(const Rail* R, const char* mot_joueur, char* lettre_rail);

/**
 * @brief Inverse une chaîne de caractères
 * @param[in,out] chaine La chaîne de caractères à inverser
 */
void inverser_chaine_caractere(char* chaine);

/**
 * @brief Réalise un "coup" d'un·e joueur·se lorsque cellui-ci dépose un mot
 * @param[in] commande La commande saisie par le/la joueur·se
 * @param[in,out] Joueur L'adresse du paquet du/de la joueur·se en question
 * @param[in] Adversaire L'adresse du paquet de l'adversaire de la/du joueur·se
 * @param[in,out] R_r L'adresse du recto du rail
 * @param[in,out] R_v L'adresse du verso du rail
 * @param[in] mot Le mot saisi par le/la joueur·se
 * @param[in] dictionnaire Adresse du dictionnaire
 * @param[in,out] motsDejaJoues Adresse des mots déjà joués
 * @return Vrai si le coup a été joué, faux sinon.
 */
int coup_joueur_R_V(const char *commande, PAQUETS *Joueur, PAQUETS *Adversaire, Rail *R_r, Rail *R_v, char *mot, const Dictionnaire* dictionnaire, Dictionnaire* motsDejaJoues);

/**
 * @brief Réalise un "coup" d'un·e joueur·se lorsque cellui-ci pioche une lettre
 * @param[in] commande La commande saisie par le/la joueur·se
 * @param[out] Joueur L'adresse du paquet du/de la joueur·se
 * @param[in,out] Pioche L'adresse de la pioche
 * @return Vrai si le coup a été joué, faux sinon
 */
int coup_joueur_echange_lettre(const char* commande, PAQUETS *Joueur, Alphabet* Pioche);

/**
 * @brief Affiche l'état du jeu
 * @param[in] J1 L'adresse du paquet du/de la joueur·se 1
 * @param[in] J2 L'adresse du paquet du/de la joueur·se 2
 * @param[in] RR L'adresse du recto du rail
 * @param[in] RV L'adresse du verso du rail
 */
void afficher_etat_jeu(const PAQUETS* J1, const PAQUETS* J2, const Rail* RR, const Rail* RV);

/**
* @brief Gère le déroulement d'un coup effectué par un·e joueur·e durant la phase principale du jeu jusqu'à ce que le coup soit valide.
* @param[in] jeu Le/la joueur·se concerné·e par le coup.
* @param[in,out] joueur L'adresse du paquet du/de la joueur·se concerné·e par le coup.
* @param[in,out] joueur_adverse L'adresse du paquet du/de la joueur·se concerné·e par le coup.
* @param[in,out] recto L'adresse du recto du rail.
* @param[in,out] verso L'adresse du verso du rail.
* @param[in,out] pioche L'adresse de la pioche.
* @param[in] Djoueur_adverse Adresse de la sauvegarde du paquet du/de la joueur·se adverse.
* @param[in] Drecto Adresse de la sauvegarde du recto du rail.
* @param[in] Dverso Adresse de la sauvegarde du verso du rail.
* @param[in] dictionnaire Adresse du dictionnaire
* @param[in,out] motsDejaJoues Adresse des mots déjà joués
*/
void gererTour(JOUEUR jeu, PAQUETS *joueur, PAQUETS *joueur_adverse, Rail *recto, Rail *verso, Alphabet *pioche, PAQUETS *Djoueur_adverse, Rail *Drecto, Rail *Dverso, const Dictionnaire* dictionnaire, Dictionnaire* motsDejaJoues);
/**
 * @brief Vide le tampon
 */
void nettoyerTampon();

/**
 * @brief Lit la commande d'un·e joueur·se
 * @param[in] commande La chaîne de caractères où est stockée la commande non formatée
 * @param[out] vrai_commande Chaine caractère de la commande formatée
 * @param[in] taille La taille de la commande à lire
 */
void lireCommande(char *commande,char vrai_commande[TAILLEMAXCOMMANDE], const size_t taille) ;

/**
* @brief Supprime tous les espaces entre le type de coup du joueur et le contenu de son coup.
* @param[in] commande Commande initialement saisie par le joueur.
* @param[out] vrai_commande Commande sans les espaces.
*/
void suppression_espace_commande(const char* commande, char* vrai_commande);

/**
 * @brief Défausse une lettre saisie dans l'entrée standard du paquet d'un·e joueur·se
 * @param[in] joueur Le/la joueur·se concerné·e
 * @param[in,out] Joueur L'adresse du paquet du/de la joueur·se.
 */
void defausse_lettre(const JOUEUR joueur, PAQUETS* Joueur);

/**
* @brief Gère la sauvegarde de l'ancienne situation de jeu sans interférer avec celle en cours.
* @param[in] Joueur1 L'adresse du paquet actuelle du/de la joueur·se 1.
* @param[in] Joueur2 L'adresse du paquet actuelle du/de la joueur·se 2.
* @param[in] R_recto L'adresse du recto du rail actuel.
* @param[in] R_verso L'adresse du verso du rail actuel.
* @param[in] Sauv_J1_n1 L'adresse du paquet au début du tour du/de la joueur·se 1.
* @param[in] Sauv_J1_n2 L'adresse du paquet au tour précédent du/de la joueur·se 2.
* @param[in] Sauv_J2_n1 L'adresse du paquet au début du tour du/de la joueur·se 1.
* @param[in] Sauv_J2_n2 L'adresse du paquet du tour précédent du/de la joueur·se 2.
* @param[in] Sauv_RR_n1 L'adresse du recto du rail au début du tour.
* @param[in] Sauv_RV_n1 L'adresse du verso du rail au début du tour.
* @param[in] Sauv_RR_n2 L'adresse du recto du rail au tour précédent.
* @param[in] Sauv_RV_n2 L'adresse du verso du rail au tour précédent.
*/
void gestion_sauvegarde(const PAQUETS *Joueur1, const PAQUETS *Joueur2, const Rail *R_recto, const Rail *R_verso,
                        PAQUETS *Sauv_J1_n1, PAQUETS *Sauv_J1_n2, PAQUETS *Sauv_J2_n1, PAQUETS *Sauv_J2_n2,
                        Rail *Sauv_RR_n1, Rail *Sauv_RV_n1, Rail *Sauv_RR_n2, Rail *Sauv_RV_n2);

/**
 * @brief Vérifie si le jeu est fini
 * @param[in] J1 L'adresse du paquet du/de la premier·e joueur·se
 * @param[in] J2 L'adresse du paquet du/de la second·e joueur·se
 * @return Vrai si le jeu est fini, faux sinon
 */
int jeu_fini(const PAQUETS* J1, const PAQUETS* J2 );