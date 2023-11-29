#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

enum Direction {NORD, SUD, EST, OUEST, NORD_EST, NORD_OUEST, SUD_EST, SUD_OUEST};

enum TypePiece {TOUR, CAVALIER, FOU, DAME, ROI, PION};

class Square {
    public:
        Square();
        Square(int rangee, int colonne);
        Square(const Square &square) ;

        Square(string square);


/**
*   @brief : convertit une case en sa notation algebrique (ex : 0,0 -> a1)
*   @return : la notation algebrique de la case
*/
        string to_string() const;

/**
*   @brief : accesseur rangée
*   @return : la rangée de la case
*/

        int getRangee() const;
        
/**
*   @brief : accesseur colonne
*   @return : la colonne de la case
*/
        int getColonne() const;
        
/**
*   @brief : setter rangée
*   @param rangee : la nouvelle rangée de la case
*/
        void setRangee(int rangee);

/**
*   @brief : setter colonne
*   @param colonne : la nouvelle colonne de la case
*/
        void setColonne(int colonne);

/**
*   @brief : setter rangée et colonne
*   @param rangee : la nouvelle rangée de la case
*   @param colonne : la nouvelle colonne de la case
*/
        void setSquare(int rangee, int colonne);

/**
*   @brief : setter case
*   @param square : la nouvelle case
*/
        void setSquare(Square square);

/**
*   @brief : vérifie si la case fait bien partie de l'échiquier
*   @return : true si la case est dans l'échiquier, false sinon
*/
        bool existe() const;

    private:
        int rangee;
        int colonne;
};

class Piece {

    public:
        Piece() ;
        Piece(TypePiece type);
        Piece(unsigned char couleur, string nom, Square square);
        Piece(TypePiece type, unsigned char couleur, string nom, Square square);
        virtual ~Piece() ;

/**
*   @brief : accesseur case pièce
*   @return : la case de la pièce
*/
        Square get_pos() const ;

/**
*   @brief : setter case pièce
*   @param square : la nouvelle case de la pièce
*/
        void set_pos(Square square) ;

/**
*   @brief : accesseur couleur pièce
*   @return : la couleur de la pièce
*/
        unsigned char get_couleur() const ;


/**
*   @brief : accesseur nom pièce
*   @return : le nom de la pièce
*/
        string get_nom() const ;

/**
*   @brief : vérifie si la pièce a déjà bougé
*   @return : true si la pièce a déjà bougé, false sinon
*/
        virtual bool a_deja_bouge_fonction() const;

/**
*   @brief : vérifie si la pièce peut se déplacer sans survoler d'autres pièces
*   @param rangee_depart : la rangée de départ
*   @param rangee_arrivee : la rangée d'arrivée
*   @param colonne_depart : la colonne de départ
*   @param colonne_arrivee : la colonne d'arrivée
*   @param echiquier: l'échiquier
*   @param dir: la direction du déplacement (ex: NORD, SUD, EST, OUEST, NORD_EST, NORD_OUEST, SUD_EST, SUD_OUEST)
*   @return : true si la pièce peut se déplacer sans survoler d'autres pièces, false sinon
*/
        virtual bool non_survol_pieces_deplacement(int rangee_depart, int rangee_arrivee, int colonne_depart, int colonne_arrivee, Piece*** echiquier, Direction dir);

/**
*   @brief : vérifie si la pièce peut se déplacer
*   @param square : la case d'arrivée
*   @param echiquier : l'échiquier
*   @return : true si la pièce peut se déplacer, false sinon
*/ 
        virtual bool deplacement(Square square, Piece*** echiquier) ;

/**
*   @brief : remplit le vecteur des cases à tester pour le pat pour cette pièce
*   @param coups_a_tester : référence vers vecteur des coups à tester
*   @param echiquier : l'échiquier
*/

        virtual void remplissage_coups_a_tester_pat(vector <Square> &coups_a_tester, Piece*** echiquier) ;

/**
*   @brief : affiche la pièce
*/
        void affiche () const ;


        TypePiece type;
        

    protected:
        unsigned char couleur;
        string nom;
        Square square_;

};

class Tour : public Piece{

    public:
        bool a_deja_bouge;

        Tour() ;
        Tour(unsigned char couleur, string nom, Square square) ;
        ~Tour() ;
        
        bool a_deja_bouge_fonction() const;
        bool non_survol_pieces_deplacement(int rangee_depart, int rangee_arrivee, int colonne_depart, int colonne_arrivee, Piece*** &echiquier, Direction dir) ;
        bool deplacement(Square square, Piece*** echiquier);
        void remplissage_coups_a_tester_pat(vector <Square> &coups_a_tester, Piece*** echiquier) ;

   
};

class Cavalier : public Piece{
    public:
        Cavalier();
        Cavalier(unsigned char couleur, string nom, Square square) ;
        ~Cavalier() ;


        bool deplacement(Square square, Piece*** echiquier) ;
        void remplissage_coups_a_tester_pat(vector <Square> &coups_a_tester, Piece*** echiquier) ;
};

class Fou : public Piece{
    public:
        Fou();
        Fou(unsigned char couleur, string nom, Square square) ;
        ~Fou() ;

        bool non_survol_pieces_deplacement(int rangee_depart, int rangee_arrivee, int colonne_depart, int colonne_arrivee, Piece*** &echiquier, Direction dir) ;


        bool deplacement(Square square, Piece*** echiquier) ;
        void remplissage_coups_a_tester_pat(vector <Square> &coups_a_tester, Piece*** echiquier) ;
  
};

class Dame : public Piece{
    public:
        Dame() ;
        Dame(unsigned char couleur, string nom, Square square) ;
        ~Dame() ;

        bool non_survol_pieces_deplacement(int rangee_depart, int rangee_arrivee, int colonne_depart, int colonne_arrivee, Piece*** &echiquier, Direction dir) ;


        bool deplacement(Square square, Piece*** echiquier) ; 
        void remplissage_coups_a_tester_pat(vector <Square> &coups_a_tester, Piece*** echiquier) ;      
};

class Roi : public Piece{
    public:
        bool a_deja_bouge;
        Roi();
        Roi(unsigned char couleur, string nom, Square square) ;
        ~Roi() ;


        bool a_deja_bouge_fonction() const;
        bool deplacement(Square square, Piece*** echiquier) ;
        void remplissage_coups_a_tester_pat(vector <Square> &coups_a_tester, Piece*** echiquier) ;
};

class Pion : public Piece{

    private :
        Square *arrivee_prise_en_passant;

    public:
        Pion() ;
        Pion(unsigned char couleur, string nom, Square square) ;
        ~Pion() ;


        bool non_survol_pieces_deplacement(int rangee_depart, int rangee_arrivee, int colonne_depart, int colonne_arrivee, Piece*** &echiquier, Direction dir) ;


        bool deplacement(Square square, Piece*** echiquier) ;
        void remplissage_coups_a_tester_pat(vector <Square> &coups_a_tester, Piece*** echiquier) ;
};


