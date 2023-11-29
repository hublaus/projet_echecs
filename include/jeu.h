#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "../include/echiquier.h"
#include "../include/piece.h"

#define Blanc 1
#define Noir 0

using namespace std;

struct Coup{
    Square origine;
    Square destination;
};

typedef enum resultat_c {COUP_ILLEGAL, COUP_NORMAL } resultat_c;

typedef enum resultat_p {PAS_DEFINI, BLANC_GAGNE, NOIR_GAGNE, VISER_LA_NULLE} resultat_p;


class Prise_en_passant{
    private :
        Piece *pion_pouvant_etre_pris_en_passant;
        vector <Coup> prises_en_passant_possibles;
        

    public : 

/**
* @brief : accesseur de pion_pouvant_etre_pris_en_passant
* @return : le pion pouvant être pris en passant
*/
        Piece* get_pion_pouvant_etre_pris_en_passant() ;
/**
* @brief : constructeur de Prise_en_passant
*/
        Prise_en_passant() ;

/**
* @brief : indique si un coup est une prise en passant possible
* @param origine : case de départ du coup
* @param destination : case d'arrivée du coup
* @return : true si le coup est une prise en passant possible, false sinon
*/
        bool est_prise_en_passant(Square origine, Square destination);

/**
* @brief : remplit le vecteur prises_en_passant_possibles avec les prises en passant possibles s'il y en a
* @param tour_des_blancs : true si c'est le tour des blancs, false sinon
* @param colonne : colonne du pion qui vient d'avancer
* @param echiquier : echiquier
*/

        void remplissage_prise_en_passant(bool tour_des_blancs, int colonne, Piece ***echiquier);

/**
* @brief : reset les vecteurs prises_en_passant_possibles et pion_pouvant_etre_pris_en_passant
*/

        void nettoyage();
};

class Jeu {

    private:
        Echiquier echiquier;
        bool tour_des_blancs;
        int compteur_coups;
        Prise_en_passant prise_en_passant;
        Piece *sauvegarde_piece_mangee;

        resultat_p resultat_partie; //initialisé par défaut à PAS_DEFINI
        resultat_c resultat_coup;   //initialisé par défaut à COUP_NORMAL

        bool stop;                  //initialisé par défaut à false


    
    public:

/**
* @brief : constructeur de la classe Jeu
*/
        Jeu() ;

/**
* @brief : setter de l'attribut stop (qui permet d'arrêter la partie)
* @param stop_ : booléen qui permet d'arrêter la partie si true
*/
        void set_stop(bool stop_);

/**
* @brief : getter de l'attribut stop
* @return : booléen qui permet d'arrêter la partie si true
*/
        bool get_stop();

/**
* @brief : permet de déterminer si un roque est possible (si ni le roi ni la tour n'ont bougé et aucune case de déplacement du roi n'est contrôlée)
* @param petit_cote : booléen qui permet de déterminer si le roque est petit ou grand
* @param couleur : couleur du joueur qui veut roquer
* @param echiquier : echiquier sur lequel on veut roquer
* @return : true si le roque est possible, false sinon
*/
        bool roque_possible(bool petit_cote, unsigned char couleur, Echiquier &echiquier);

/**
*@brief effectue le roque
*@param petit_cote : true si le roque est petit, false si le roque est grand
*@param couleur : 1 si le roque est blanc, 0 si le roque est noir
*@param echiquier : l'echiquier sur lequel on joue
*/
        void effectuer_roque(bool petit_cote, unsigned char couleur, Echiquier &echiquier);

/**
*@brief effectue un déplacement après une entrée de l'utilisateur, et actualise les paramètres de jeu (si coup illégal, rien n'est modifié et un message demande de rejouer)
*@param orig : la case de depart
*@param dest : la case d'arrivee
*/
        void deplace(std::string orig, std::string dest) ;



/**
* @brief Affiche l'échiquier
*/
        void affiche() {
            this->echiquier.affiche();
            return;
        }

/**
* @brief Affiche la position finale ainsi que le résultat de la partie
*/
        void affiche_fin() ;


};
