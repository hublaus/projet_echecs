#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "../include/piece.h"

using namespace std;

#define NBCOL 8
#define Blanc 1
#define Noir 0


class Echiquier {

    private:
        Piece ***echiquier;

        vector<Piece*> piecesb;
        vector<Piece*> piecesn;
        vector<Piece*> pionsb;
        vector<Piece*> pionsn;


    public:

        Piece*** get_echiquier() ;

        Piece *getPiece(Square square) ;

        Piece *getPiece(int rangee, int colonne) ;


    /**
    * @brief : alloue un tableau équivalent à un Piece *[8][8] en initialisant les cases à nullptr et alloue des vecteurs piecesb, piecesn, pionsb et pionsn
    */
        void alloc_mem_echiquier() ;


    /*
    * @brief : fonction appelée si le coup joué est un coup de pion
    * @brief : si le pion arrive sur la dernière rangée, on demande au joueur quelle pièce il veut
    * @brief : alors le pion est supprimé, et une pièce est créée à la place (et intégrée dans le vecteur piecesb ou piecesn)
    * @param piece : pointeur vers la pièce à ajouter (le même que celui de la nouvelle pièce créée)
    * @param square : case où ajouter la pièce
    */
        void promotion(Piece* &piece, Square square) ;

    /*
    * @brief : si la case d'arrivée n'est pas occupée, on y pose la pièce (sinon on affiche un message d'erreur)
    * @param : piece : pointeur vers la pièce à poser
    * @param : square : case où poser la pièce
    */
        void pose_piece(Piece* piece, Square square) ;
    /*
    * @brief : si case occupée, on l'enlève simplement sans la supprimer (sinon, affiche un message d'erreur)
    * @param : square : case où enlever la pièce
    */
        void depart_piece(Square square) ;

    /*
    * @brief : enlève la pièce de sa case, et du vecteur de pièces ou pions où elle se trouve
    * @brief : la pièce n'est cependant pas supprimée définitivement, et pourra être rescussitée par resurrection_piece si sauvegardée (mémoire pas libérée)
    * @param : piece : pointeur vers la pièce à enlever
    */
        void mort_piece(Piece *piece);
    /*
    * @brief : même chose que fonction précédente, mais avec une case en paramètre
    * @param : square : case où enlever la pièce
    */
        void mort_piece(Square square) ;

    /*
    * @brief : remet la pièce sur l'échiquier, et dans le vecteur de pièces ou pions où elle se trouvait
    * @param : piece : pointeur vers la pièce à remettre
    */
        void resurrection_piece(Piece *piece) ;


    /*
    * @brief : effectue un coup (départ et arrivée pièce), et sauvegarde la pièce mangée (si il y en a une)
    * @param : origine : case de départ de la pièce
    * @param : destination : case d'arrivée de la pièce
    * @param : sauvegarde_piece_mangee : pointeur vers la pièce mangée (nullptr si aucune)
    */
        void effectuer_coup(Square origine, Square destination, Piece* &sauvegarde_piece_mangee) ;

    /*
    * @brief : annule un coup (départ et arrivée pièce), et remet la pièce mangée (si il y en a une)
    * @param : origine : case de départ de la pièce
    * @param : destination : case d'arrivée de la pièce
    * @param : sauvegarde_piece_mangee : pointeur vers la pièce mangée (nullptr si aucune)
    */    
        void annuler_coup(Square origine, Square destination, Piece* &sauvegarde_piece_mangee) ;

    /*
    * @brief : indique si une pièce correspond à un nom donné
    * @param : piece : pointeur vers la pièce à tester
    * @param : nom : nom à tester
    * @return : true si le nom correspond, false sinon
    */
        bool nom_correspondant_piece(Piece *piece, string &nom) ;







    /*
    * @brief : indique si une case attaquée par un pion de la couleur adverse
    * @param : case_ : case à tester
    * @param : couleur : couleur des pièces alliées
    * @return : true si la case est attaquée par un pion, false sinon
    */
        bool case_attaquee_par_pion(Square case_, unsigned int couleur) ;
    /*
    * @brief : indique si une case attaquée par une pièce (autre que pion) de la couleur adverse
    * @param : case_ : case à tester
    * @param : couleur : couleur des pièces alliées
    * @return : true si la case est attaquée par une pièce, false sinon
    */    
        bool case_attaquee_par_piece(Square case_, unsigned int couleur) ;

    /*
    * @brief : renvoie un pointeur vers le pion attaquant la case, si il y en a un
    * @param : case_ : case à tester
    * @param : couleur : couleur des pièces alliées
    * @return : pointeur vers le pion attaquant la case, nullptr sinon
    */
        Piece* case_attaquee_par_pion_attaquant(Square case_, unsigned int couleur);

    /*
    * @brief : si un pion attaque le roi, est ajouté au vecteur pieces_attaquantes
    * @param : couleur : couleur des pièces alliées
    * @param : pieces_attaquantes : vecteur de pointeurs vers les pièces attaquantes
    */
        void remplissage_attaquants_roi_pion_potentiel(unsigned int couleur, vector <Piece*> &pieces_attaquantes) ;
    /*
    * @brief : indique si une pièce ou un pion adverse attaque la case
    * @param : case_ : case à tester
    * @param : couleur : couleur des pièces alliées
    * @return : true si la case est attaquée, false sinon
    */
        bool case_attaquee(Square case_, unsigned int couleur) ;

    /*
    * @brief : indique si un pion adverse attaque le roi
    * @param : couleur : couleur des pièces alliées
    * @return : true si le roi est attaqué, false sinon
    */
        bool detection_echec_pion(unsigned int couleur) ;

    /*
    * @brief : remplissage du vecteur pieces_attaquantes avec les pièces adverses attaquant le roi
    * @param : couleur : couleur des pièces alliées
    * @param : pieces_attaquantes : vecteur de pointeurs vers les pièces attaquantes
    */
        void remplissage_attaquants_roi(unsigned int couleur, vector <Piece*> &pieces_attaquantes) ;

    /*
    * @brief : indique si une pièce adverse attaque le roi (s'arrête dès qu'une pièce est trouvée)
    * @param : couleur : couleur des pièces alliées
    * @return : true si le roi est attaqué, false sinon
    */    
        bool detection_echec(unsigned int couleur) ;

    /*
    * @brief : indique si le roi peut se déplacer (sans être attaqué)
    * @param : couleur : couleur des pièces alliées
    * @return : true si le roi peut se déplacer, false sinon
    */
        bool coup_roi_disponible(unsigned int couleur);

    /*
    * @brief : indique si un echec peut être paré en éliminant l'attaquant
    * @param : attaquant : pointeur vers la pièce attaquante
    * @param : couleur : couleur des pièces alliées
    * @return : true si l'attaque peut être parée, false sinon
    */
        bool prise_pour_parer_echec_possible(Piece* attaquant, unsigned int couleur) ;

    /*
    * @brief : indique si un echec peut être paré en bloquant l'attaque en se déplaçant sur une certaine case
    * @param : case_ : case sur laquelle se déplacer pour bloquer l'attaque
    * @param : couleur : couleur des pièces alliées
    * @return : true si l'attaque peut être parée, false sinon
    */    
        bool blocage_echec_possible(Square case_, unsigned int couleur) ;
    
    /*
    * @brief : indique si le roi allié est en echec et mat
    * @param : couleur : couleur des pièces alliées
    * @return : true si le roi est en echec et mat, false sinon
    */
        bool detection_echec_et_mat(unsigned int couleur) ;

    /*
    * @brief : indique si le roi allié est en pat
    * @param : couleur : couleur des pièces alliées
    * @return : true si le roi est en pat, false sinon
    */
        bool detection_pat(unsigned int couleur) ;


    /*
    * @brief : constructeur echiquier : alloue les vecteurs de pièces et les pièces, l'échiquier en position initiale
    */
        Echiquier () ;
    /*
    * @brief : libère un vecteur de pièces
    */
        void libere(vector<Piece*> vecteur);

    /*
    * @brief : destructeur echiquier : libère les vecteurs de pièces et les pièces, ainsi que l'échiquier
    */
        ~Echiquier () ;
    
    /*
    * @brief : affiche l'échiquier dans sa position actuelle
    */
        void affiche () const ;

    /*
    * @brief : effectue un coup si possible, sinon demande à l'utilisateur de saisir un nouveau coup ; puis actualise les nouvelles conditions de jeu (mat, prise en passant possible ...)
    */
        void deplace() ;


        string pgn_piece_name(string const name, bool view_pawn, bool view_color) ;

        string canonical_position() ;

};