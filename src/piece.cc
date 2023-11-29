#include <iostream>
#include <vector>
#include <string>
#include "../include/piece.h"
using namespace std;

/**
*   @file piece.cc : contient les fonctions relatives à la classe Piece et à ses classes filles, ainsi que la classe Square
*/

    Square::Square() : rangee(0), colonne(0) {};
    Square::Square(int rangee, int colonne) : rangee(rangee), colonne(colonne) {};
    Square::Square(const Square &square) : rangee(square.rangee), colonne(square.colonne) {};

    Square::Square(string square) {
        this->rangee = square[1] - '1';
        this->colonne = square[0] - 'a';
        return;
    }

    string Square::to_string() const {
        string square;
        square += 'a' + this->colonne;
        square += '1' + this->rangee;
        return square;
    }

    int Square::getRangee() const {
        return this->rangee;
    }
    
    int Square::getColonne() const {
        return this->colonne;
    }
    
    void Square::setRangee(int rangee) {
        this->rangee = rangee;
        return;
    }

    void Square::setColonne(int colonne) {
        this->colonne = colonne;
        return;
    }

    void Square::setSquare(int rangee, int colonne) {
        this->rangee = rangee;
        this->colonne = colonne;
        return;
    }

    void Square::setSquare(Square square) {
        this->rangee = square.rangee;
        this->colonne = square.colonne;
        return;
    }

    bool Square::existe() const{
        if (this->rangee < 0 || this->rangee > 7 || this->colonne < 0 || this->colonne > 7) {
            return false;
        }
        return true;
    }





    Piece::Piece(TypePiece type): type(type) {};
    Piece::Piece(unsigned char couleur, string nom, Square square) : couleur(couleur), nom(nom), square_(square) {};
    Piece::Piece(TypePiece type, unsigned char couleur, string nom, Square square) : type(type), couleur(couleur), nom(nom), square_(square) {};

    Piece::~Piece() {
        return;
    }


    Square Piece::get_pos() const {
        return this->square_;
    }

    void Piece::set_pos(Square square) {
        this->square_ = square;
        return;
    }

    unsigned char Piece::get_couleur() const {
        return this->couleur;
    }

    string Piece::get_nom() const {
        return this->nom;
    }

    bool Piece::a_deja_bouge_fonction() const {
        return true;
    }

    bool Piece::non_survol_pieces_deplacement(int rangee_depart, int rangee_arrivee, int colonne_depart, int colonne_arrivee, Piece*** echiquier, Direction dir) {
        return true;
    }


    bool Piece::deplacement(Square square, Piece*** echiquier) {
        return true;
    } 

    void Piece::remplissage_coups_a_tester_pat(vector <Square> &coups_a_tester, Piece*** echiquier) {
        return;
    }


    void Piece::affiche () const {
        cout << this->nom;
        return;
    }


    Tour::Tour() : Piece(TOUR), a_deja_bouge(false) {};
    Tour::Tour(unsigned char couleur, string nom, Square square) : Piece(TOUR, couleur, nom, square), a_deja_bouge(false) {};

    Tour::~Tour() {
        return;
    }

    bool Tour::a_deja_bouge_fonction() const {
        return this->a_deja_bouge;
    }

    bool Tour::non_survol_pieces_deplacement(int rangee_depart, int rangee_arrivee, int colonne_depart, int colonne_arrivee, Piece*** &echiquier, Direction dir) {
        switch (dir){
            case NORD:
                for (int i = rangee_depart + 1; i < rangee_arrivee; i++) {
                    if (echiquier[i][colonne_depart] != nullptr) {
                        return false;
                    }
                }
                return true;
                break;
            case SUD:
                for (int i = rangee_depart - 1; i > rangee_arrivee; i--) {
                    if (echiquier[i][colonne_depart] != nullptr) {
                        return false;
                    }
                }
                return true;
                break;
            case EST:
                for (int i = colonne_depart + 1; i < colonne_arrivee; i++) {
                    if (echiquier[rangee_depart][i] != nullptr) {
                        return false;
                    }
                }
                return true;
                break;
            case OUEST:
                for (int i = colonne_depart - 1; i > colonne_arrivee; i--) {
                    if (echiquier[rangee_depart][i] != nullptr) {
                        return false;
                    }
                }
                return true;
                break;
            default:
                cout << "Erreur dans la direction" << endl;
                return false;
                break;
        }
        return false;
    }



    bool Tour::deplacement(Square square, Piece*** echiquier) {

        int rangee = square.getRangee();
        int colonne = square.getColonne();

        int rangee_actuelle = this->square_.getRangee();
        int colonne_actuelle = this->square_.getColonne();

        if (echiquier [rangee][colonne] != nullptr) {
            if (echiquier [rangee][colonne]->get_couleur() == this->couleur) {
                cout << "Il y a une piece de la meme couleur sur la case d'arrivée" << endl;
                return false;
            }
        }

        if (rangee == rangee_actuelle) {
            Direction dir = OUEST;
            if (colonne > colonne_actuelle) {
                dir = EST;
            }
            if (this->non_survol_pieces_deplacement(rangee_actuelle, rangee, colonne_actuelle, colonne, echiquier, dir)) {
                cout << "Deplacement valide" << endl;
                //this->set_pos(square);
                return true;
            }
            else {
                cout << "Il y a une piece sur le chemin" << endl;
                return false;
            }
        }

        else if(colonne == colonne_actuelle) {
            Direction dir = SUD;
            if (rangee > rangee_actuelle) {
                dir = NORD;
            }
            if (this->non_survol_pieces_deplacement(rangee_actuelle, rangee, colonne_actuelle, colonne, echiquier, dir)) {
                cout << "Deplacement valide" << endl;
                //this->set_pos(square);
                return true;
            }
            else {
                return false;
            }
        }

        else {
            return false;
        }

    }

    void Tour::remplissage_coups_a_tester_pat(vector <Square> &coups_a_tester, Piece*** echiquier){
        int rangee = this->square_.getRangee();
        int colonne = this->square_.getColonne();

        Square coup(rangee, colonne + 1);
        if (coup.existe()){
            if ( (echiquier[rangee][colonne + 1] == nullptr) || (echiquier[rangee][colonne + 1]->get_couleur() != this->couleur) ){
                coups_a_tester.push_back(coup);
            }
        }

        coup.setSquare(rangee, colonne - 1);
        if (coup.existe()){
            if ( (echiquier[rangee][colonne - 1] == nullptr) || (echiquier[rangee][colonne - 1]->get_couleur() != this->couleur) ){
                coups_a_tester.push_back(coup);
            }
        }
        
        coup.setSquare(rangee + 1, colonne);
        if (coup.existe()){
            if ( (echiquier[rangee + 1][colonne] == nullptr) || (echiquier[rangee + 1][colonne]->get_couleur() != this->couleur) ){
                coups_a_tester.push_back(coup);
            }
        }

        coup.setSquare(rangee - 1, colonne);
        if (coup.existe()){
            if ( (echiquier[rangee - 1][colonne] == nullptr) || (echiquier[rangee - 1][colonne]->get_couleur() != this->couleur) ){
                coups_a_tester.push_back(coup);
            }
        }

        return;
    }


    Cavalier::Cavalier() : Piece(CAVALIER) {};
    Cavalier::Cavalier(unsigned char couleur, string nom, Square square) : Piece(CAVALIER, couleur, nom, square) {};
    Cavalier::~Cavalier() {
        return;
    }


    bool Cavalier::deplacement(Square square, Piece*** echiquier) {
        int rangee = square.getRangee();
        int colonne = square.getColonne();

        int rangee_actuelle = this->square_.getRangee();
        int colonne_actuelle = this->square_.getColonne();

        if (echiquier [rangee][colonne] != nullptr) {
            if (echiquier [rangee][colonne]->get_couleur() == this->couleur) {
                cout << "Il y a une piece de la meme couleur sur la case d'arrivée" << endl;
                return false;
            }
        }    

        if ((rangee == rangee_actuelle + 2 && colonne == colonne_actuelle + 1) || (rangee == rangee_actuelle + 2 && colonne == colonne_actuelle - 1) || (rangee == rangee_actuelle - 2 && colonne == colonne_actuelle + 1) || (rangee == rangee_actuelle - 2 && colonne == colonne_actuelle - 1) || (rangee == rangee_actuelle + 1 && colonne == colonne_actuelle + 2) || (rangee == rangee_actuelle + 1 && colonne == colonne_actuelle - 2) || (rangee == rangee_actuelle - 1 && colonne == colonne_actuelle + 2) || (rangee == rangee_actuelle - 1 && colonne == colonne_actuelle - 2)) {
            //pas besoin de test de non survol de pieces car le cavalier saute par dessus
            //set_pos(square);
            return true;
        }
        else {
            return false;
        }
    }

    void Cavalier::remplissage_coups_a_tester_pat(vector <Square> &coups_a_tester, Piece*** echiquier) {
        int rangee = this->square_.getRangee();
        int colonne = this->square_.getColonne();

        Square coup(rangee + 2, colonne + 1);
        if (coup.existe()){
            if ( (echiquier[rangee + 2][colonne + 1] == nullptr) || (echiquier[rangee + 2][colonne + 1]->get_couleur() != this->couleur) ){
                coups_a_tester.push_back(coup);
            }
        }

        coup.setSquare(rangee + 2, colonne - 1);
        if (coup.existe()){
            if ( (echiquier[rangee + 2][colonne - 1] == nullptr) || (echiquier[rangee + 2][colonne - 1]->get_couleur() != this->couleur) ){
                coups_a_tester.push_back(coup);
            }
        }

        coup.setSquare(rangee - 2, colonne + 1);
        if (coup.existe()){
            if ( (echiquier[rangee - 2][colonne + 1] == nullptr) || (echiquier[rangee - 2][colonne + 1]->get_couleur() != this->couleur) ){
                coups_a_tester.push_back(coup);
            }
        }

        coup.setSquare(rangee - 2, colonne - 1);
        if (coup.existe()){
            if ( (echiquier[rangee - 2][colonne - 1] == nullptr) || (echiquier[rangee - 2][colonne - 1]->get_couleur() != this->couleur) ){
                coups_a_tester.push_back(coup);
            }
        }

        coup.setSquare(rangee + 1, colonne + 2);
        if (coup.existe()){
            if ( (echiquier[rangee + 1][colonne + 2] == nullptr) || (echiquier[rangee + 1][colonne + 2]->get_couleur() != this->couleur) ){
                coups_a_tester.push_back(coup);
            }
        }

        coup.setSquare(rangee + 1, colonne - 2);
        if (coup.existe()){
            if ( (echiquier[rangee + 1][colonne - 2] == nullptr) || (echiquier[rangee + 1][colonne - 2]->get_couleur() != this->couleur) ){
                coups_a_tester.push_back(coup);
            }
        }

        coup.setSquare(rangee - 1, colonne + 2);
        if (coup.existe()){
            if ( (echiquier[rangee - 1][colonne + 2] == nullptr) || (echiquier[rangee - 1][colonne + 2]->get_couleur() != this->couleur) ){
                coups_a_tester.push_back(coup);
            }
        }

        coup.setSquare(rangee - 1, colonne - 2);
        if (coup.existe()){
            if ( (echiquier[rangee - 1][colonne - 2] == nullptr) || (echiquier[rangee - 1][colonne - 2]->get_couleur() != this->couleur) ){
                coups_a_tester.push_back(coup);
            }
        }

        return;
    }


    Fou::Fou() : Piece(FOU) {};
    Fou::Fou(unsigned char couleur, string nom, Square square) : Piece(FOU, couleur, nom, square) {};
    Fou::~Fou() {
        return;
    }

    bool Fou::non_survol_pieces_deplacement(int rangee_depart, int rangee_arrivee, int colonne_depart, int colonne_arrivee, Piece*** &echiquier, Direction dir) {
        switch (dir) {
            case NORD_EST:
                for (int i = rangee_depart + 1; i < rangee_arrivee; i++) {
                    if (echiquier[i][colonne_depart + (i - rangee_depart)] != nullptr) {
                        return false;
                    }
                }
                return true;
                break;
            case NORD_OUEST:
                for (int i = rangee_depart + 1; i < rangee_arrivee; i++) {
                    if (echiquier[i][colonne_depart - (i - rangee_depart)] != nullptr) {
                        return false;
                    }
                }
                return true;
                break;
            case SUD_EST:
                for (int i = rangee_depart - 1; i > rangee_arrivee; i--) {
                    if (echiquier[i][colonne_depart + (rangee_depart - i)] != nullptr) {
                        return false;
                    }
                }
                return true;
                break;
            case SUD_OUEST:
                for (int i = rangee_depart - 1; i > rangee_arrivee; i--) {
                    if (echiquier[i][colonne_depart - (rangee_depart - i)] != nullptr) {
                        return false;
                    }
                }
                return true;
                break;
            default:
                return false;
                break;
        }
        return false;
    }


    bool Fou::deplacement(Square square, Piece*** echiquier) {
        int rangee = square.getRangee();
        int colonne = square.getColonne();
    
        int rangee_actuelle = this->square_.getRangee();
        int colonne_actuelle = this->square_.getColonne(); 


        if (echiquier [rangee][colonne] != nullptr) {
            if (echiquier [rangee][colonne]->get_couleur() == this->couleur) {
                cout << "Il y a une piece de la meme couleur sur la case d'arrivée" << endl;
                return false;
            }
        }      
    

        if (rangee - rangee_actuelle == colonne - colonne_actuelle) {
            
            Direction dir = NORD_EST;
            if (rangee < rangee_actuelle) {
                dir = SUD_OUEST;
            }

            if (this->non_survol_pieces_deplacement(rangee_actuelle, rangee, colonne_actuelle, colonne, echiquier, dir )) {
                //this->set_pos(square);
                return true;
            }
            else {
                cout << "Il y a une piece sur le chemin" << endl;
                return false;
            }
        }
        else if (rangee - rangee_actuelle == colonne_actuelle - colonne) {
            
            Direction dir = NORD_OUEST;
            if (rangee < rangee_actuelle) {
                dir = SUD_EST;
            }

            if (this->non_survol_pieces_deplacement(rangee_actuelle, rangee, colonne_actuelle, colonne, echiquier, dir)) {
                //this->set_pos(square);
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }

    void Fou::remplissage_coups_a_tester_pat(vector <Square> &coups_a_tester, Piece*** echiquier) {
        int rangee = this->square_.getRangee();
        int colonne = this->square_.getColonne();

        Square coup(rangee + 1, colonne + 1);
        if (coup.existe()){
            if ( (echiquier[rangee + 1][colonne + 1] == nullptr) || (echiquier[rangee + 1][colonne + 1]->get_couleur() != this->couleur) ){
                coups_a_tester.push_back(coup);
            }
        }
        coup.setSquare(rangee + 1, colonne - 1);
        if (coup.existe()){
            if ( (echiquier[rangee + 1][colonne - 1] == nullptr) || (echiquier[rangee + 1][colonne - 1]->get_couleur() != this->couleur) ){
                coups_a_tester.push_back(coup);
            }
        }

        coup.setSquare(rangee - 1, colonne + 1);
        if (coup.existe()){
            if ( (echiquier[rangee - 1][colonne + 1] == nullptr) || (echiquier[rangee - 1][colonne + 1]->get_couleur() != this->couleur) ){
                coups_a_tester.push_back(coup);
            }
        }

        coup.setSquare(rangee - 1, colonne - 1);
        if (coup.existe()){
            if ( (echiquier[rangee - 1][colonne - 1] == nullptr) || (echiquier[rangee - 1][colonne - 1]->get_couleur() != this->couleur) ){
                coups_a_tester.push_back(coup);
            }
        }

        return;
    }


    Dame::Dame() : Piece(DAME) {};
    Dame::Dame(unsigned char couleur, string nom, Square square) : Piece(DAME, couleur, nom, square) {};
    Dame::~Dame() {
        return;
    }

    bool Dame::non_survol_pieces_deplacement(int rangee_depart, int rangee_arrivee, int colonne_depart, int colonne_arrivee, Piece*** &echiquier, Direction dir) {
        
        switch (dir){
            case NORD:
                for (int i = rangee_depart + 1; i < rangee_arrivee; i++) {
                    if (echiquier[i][colonne_depart] != nullptr) {
                        return false;
                    }
                }
                return true;
                break;
            case SUD:
                for (int i = rangee_depart - 1; i > rangee_arrivee; i--) {
                    if (echiquier[i][colonne_depart] != nullptr) {
                        return false;
                    }
                }
                return true;
                break;
            case EST:
                for (int i = colonne_depart + 1; i < colonne_arrivee; i++) {
                    if (echiquier[rangee_depart][i] != nullptr) {
                        return false;
                    }
                }
                return true;
                break;
            case OUEST:
                for (int i = colonne_depart - 1; i > colonne_arrivee; i--) {
                    if (echiquier[rangee_depart][i] != nullptr) {
                        return false;
                    }
                }
                return true;
                break;
            case NORD_EST:
                for (int i = rangee_depart + 1; i < rangee_arrivee; i++) {
                    if (echiquier[i][colonne_depart + (i - rangee_depart)] != nullptr) {
                        return false;
                    }
                }
                return true;
                break;
            case NORD_OUEST:
                for (int i = rangee_depart + 1; i < rangee_arrivee; i++) {
                    if (echiquier[i][colonne_depart - (i - rangee_depart)] != nullptr) {
                        return false;
                    }
                }
                return true;
                break;
            case SUD_EST:
                for (int i = rangee_depart - 1; i > rangee_arrivee; i--) {
                    if (echiquier[i][colonne_depart + (rangee_depart - i)] != nullptr) {
                        return false;
                    }
                }
                return true;
                break;
            case SUD_OUEST:
                for (int i = rangee_depart - 1; i > rangee_arrivee; i--) {
                    if (echiquier[i][colonne_depart - (rangee_depart - i)] != nullptr) {
                        return false;
                    }
                }
                return true;
                break;

        }
        return false;
    }


    bool Dame::deplacement(Square square, Piece*** echiquier) {
        int rangee = square.getRangee();
        int colonne = square.getColonne();

        int rangee_actuelle = this->square_.getRangee();
        int colonne_actuelle = this->square_.getColonne();

        if (echiquier[rangee][colonne] != nullptr) {
            if (echiquier[rangee][colonne]->get_couleur() == this->couleur) {
                return false;
            }
        }         


        if (rangee == rangee_actuelle) { // cas ou la dame se deplace horizontalement
            Direction dir = OUEST;
            if (colonne > colonne_actuelle) {
                dir = EST;
            }
            if (this->non_survol_pieces_deplacement(rangee_actuelle, rangee, colonne_actuelle, colonne, echiquier, dir)) {
                return true;
            }
            else {
                return false;
            }
        }

        else if (colonne == colonne_actuelle){ // cas ou la dame se deplace verticalement
            Direction dir = SUD;
            if (rangee > rangee_actuelle) {
                dir = NORD;
            }
            if (this->non_survol_pieces_deplacement(rangee_actuelle, rangee, colonne_actuelle, colonne, echiquier, dir)) {
                //this->set_pos(square);
                return true;
            }
            else {
                return false;
            }
        } // cas ou la dame se deplace verticalement

        else if (rangee - rangee_actuelle == colonne - colonne_actuelle){
            Direction dir = NORD_EST;
            if (rangee < rangee_actuelle) {
                dir = SUD_OUEST;
            }

            if (this->non_survol_pieces_deplacement(rangee_actuelle, rangee, colonne_actuelle, colonne, echiquier, dir )) {
                //this->set_pos(square);
                return true;
            }
            else {
                return false;
            }
        } // cas où la dame se déplace en diagonale nord est // sud ouest

        else if (rangee - rangee_actuelle == colonne_actuelle - colonne){
            Direction dir = NORD_OUEST;
            if (rangee < rangee_actuelle) {
                dir = SUD_EST;
            }

            if (this->non_survol_pieces_deplacement(rangee_actuelle, rangee, colonne_actuelle, colonne, echiquier, dir)) {
                //this->set_pos(square);
                return true;
            }
            else {
                return false;
            }
        } // cas où la dame se déplace en diagonale nord ouest // sud est

        else {
            return false;
        }
    }

    void Dame::remplissage_coups_a_tester_pat(vector <Square> &coups_a_tester, Piece*** echiquier) {
        int rangee = this->square_.getRangee();
        int colonne = this->square_.getColonne();

        Square coup(rangee, colonne+1);
        if (coup.existe()){
            if ( (echiquier[rangee][colonne+1] == nullptr ) || (echiquier[rangee][colonne+1]->get_couleur() != this->couleur) ){
                coups_a_tester.push_back(coup);
            }
        }

        coup.setSquare(rangee, colonne-1);
        if (coup.existe()){
            if ( (echiquier[rangee][colonne-1] == nullptr ) || (echiquier[rangee][colonne-1]->get_couleur() != this->couleur) ){
                coups_a_tester.push_back(coup);
            }
        }

        coup.setSquare(rangee+1, colonne);
        if (coup.existe()){
            if ( (echiquier[rangee+1][colonne] == nullptr ) || (echiquier[rangee+1][colonne]->get_couleur() != this->couleur) ){
                coups_a_tester.push_back(coup);
            }
        }

        coup.setSquare(rangee-1, colonne);
        if (coup.existe()){
            if ( (echiquier[rangee-1][colonne] == nullptr ) || (echiquier[rangee-1][colonne]->get_couleur() != this->couleur) ){
                coups_a_tester.push_back(coup);
            }
        }

        coup.setSquare(rangee+1, colonne+1);
        if (coup.existe()){
            if ( (echiquier[rangee+1][colonne+1] == nullptr ) || (echiquier[rangee+1][colonne+1]->get_couleur() != this->couleur) ){
                coups_a_tester.push_back(coup);
            }
        }

        coup.setSquare(rangee+1, colonne-1);
        if(coup.existe()){
            if ( (echiquier[rangee+1][colonne-1] == nullptr ) || (echiquier[rangee+1][colonne-1]->get_couleur() != this->couleur) ){
                coups_a_tester.push_back(coup);
            }
        }

        coup.setSquare(rangee-1, colonne+1);
        if (coup.existe()){
            if ( (echiquier[rangee-1][colonne+1] == nullptr ) || (echiquier[rangee-1][colonne+1]->get_couleur() != this->couleur) ){
                coups_a_tester.push_back(coup);
            }
        }

        coup.setSquare(rangee-1, colonne-1);
        if (coup.existe()){
            if ( (echiquier[rangee-1][colonne-1] == nullptr ) || (echiquier[rangee-1][colonne-1]->get_couleur() != this->couleur) ){
                coups_a_tester.push_back(coup);
            }
        }

        return;

    }


    Roi::Roi() : Piece(ROI), a_deja_bouge(false) {};
    Roi::Roi(unsigned char couleur, string nom, Square square) : Piece(ROI, couleur, nom, square), a_deja_bouge(false) {};
    Roi::~Roi() {};

    bool Roi::a_deja_bouge_fonction() const {
        return this->a_deja_bouge;
    }

    /*bool Tour::a_deja_bouge_fonction() const {
        return this->a_deja_bouge;
    }*/

    bool Roi::deplacement(Square square, Piece*** echiquier) {
        int rangee = square.getRangee();
        int colonne = square.getColonne();

        int rangee_actuelle = this->square_.getRangee();
        int colonne_actuelle = this->square_.getColonne();

        if (echiquier[rangee][colonne] != nullptr && echiquier[rangee][colonne]->get_couleur() == this->couleur) {
            return false;
        }

        if ((rangee == rangee_actuelle + 1 && colonne == colonne_actuelle) || (rangee == rangee_actuelle - 1 && colonne == colonne_actuelle) || (rangee == rangee_actuelle && colonne == colonne_actuelle + 1) || (rangee == rangee_actuelle && colonne == colonne_actuelle - 1) || (rangee == rangee_actuelle + 1 && colonne == colonne_actuelle + 1) || (rangee == rangee_actuelle + 1 && colonne == colonne_actuelle - 1) || (rangee == rangee_actuelle - 1 && colonne == colonne_actuelle + 1) || (rangee == rangee_actuelle - 1 && colonne == colonne_actuelle - 1)) {
            //set_pos(square);
            return true;
        }
        else {
            return false;
        }
    }

    void Roi::remplissage_coups_a_tester_pat(vector <Square> &coups_a_tester, Piece*** echiquier) {
        int rangee = this->square_.getRangee();
        int colonne = this->square_.getColonne();

        Square coup(rangee, colonne+1);
        if (coup.existe()){
            if ( (echiquier[rangee][colonne+1] == nullptr) || (echiquier[rangee][colonne+1]->get_couleur() != this->couleur) ){
                coups_a_tester.push_back(coup);
            }
        }


        coup.setSquare(rangee, colonne-1);
        if (coup.existe()){
            if ( (echiquier[rangee][colonne-1] == nullptr) || (echiquier[rangee][colonne-1]->get_couleur() != this->couleur) ){
                coups_a_tester.push_back(coup);
            }
        }

        coup.setSquare(rangee+1, colonne);
        if (coup.existe()){
            if ( (echiquier[rangee+1][colonne] == nullptr) || (echiquier[rangee+1][colonne]->get_couleur() != this->couleur) ){
                coups_a_tester.push_back(coup);
            }
        }

        coup.setSquare(rangee-1, colonne);
        if (coup.existe()){
            if ( (echiquier[rangee-1][colonne] == nullptr) || (echiquier[rangee-1][colonne]->get_couleur() != this->couleur) ){
                coups_a_tester.push_back(coup);
            }
        }

        coup.setSquare(rangee+1, colonne+1);
        if (coup.existe()){
            if ( (echiquier[rangee+1][colonne+1] == nullptr) || (echiquier[rangee+1][colonne+1]->get_couleur() != this->couleur) ){
                coups_a_tester.push_back(coup);
            }
        }

        coup.setSquare(rangee+1, colonne-1);
        if (coup.existe()){
            if ( (echiquier[rangee+1][colonne-1] == nullptr) || (echiquier[rangee+1][colonne-1]->get_couleur() != this->couleur) ){
                coups_a_tester.push_back(coup);
            }
        }

        coup.setSquare(rangee-1, colonne+1);
        if (coup.existe()){
            if ( (echiquier[rangee-1][colonne+1] == nullptr) || (echiquier[rangee-1][colonne+1]->get_couleur() != this->couleur) ){
                coups_a_tester.push_back(coup);
            }
        }
        

        
        coup.setSquare(rangee-1, colonne-1);
        if (coup.existe()){
            if ( (echiquier[rangee-1][colonne-1] == nullptr) || (echiquier[rangee-1][colonne-1]->get_couleur() != this->couleur) ){
                coups_a_tester.push_back(coup);
            }
        }
        return;

    }


    Pion::Pion() : Piece(PION), arrivee_prise_en_passant(nullptr) {};
    Pion::Pion(unsigned char couleur, string nom, Square square) : Piece(PION, couleur, nom, square), arrivee_prise_en_passant(nullptr) {};
    Pion::~Pion() {};


    bool Pion::non_survol_pieces_deplacement(int rangee_depart, int rangee_arrivee, int colonne_depart, int colonne_arrivee, Piece*** &echiquier, Direction dir) {
        //dir vaut forcément NORD ou SUD

        switch (dir){
            case NORD : 
                if (echiquier[2][colonne_depart] != nullptr) {
                    return false;
                }
                return true;

            case SUD : 
                if (echiquier[5][colonne_depart] != nullptr) {
                    return false;
                }
                return true;
            default : 
                return false;
        }

        return true;
    }

    bool Pion::deplacement(Square square, Piece*** echiquier) {
        int rangee = square.getRangee();
        int colonne = square.getColonne();

        int rangee_actuelle = this->square_.getRangee();
        int colonne_actuelle = this->square_.getColonne();

        if (colonne == colonne_actuelle){
            if (echiquier[rangee][colonne] != nullptr) { // si il y a une piece sur la case d'arrivée
                return false;
            }
        }

        if (this->couleur == 1) {
            if (rangee == rangee_actuelle + 1 && colonne == colonne_actuelle) {
                //set_pos(square);
                return true;
            }
            else if (rangee_actuelle == 1 && rangee == 3 && colonne == colonne_actuelle){
                if ( non_survol_pieces_deplacement(rangee_actuelle, rangee, colonne_actuelle, colonne, echiquier, NORD) ){
                    cout << "ok" << endl;
                    //set_pos(square);
                    return true;
                }
                else { // si il y a une piece sur le chemin
                    return false;
                }
            }

            else if (rangee == rangee_actuelle + 1 && (colonne == colonne_actuelle + 1 || colonne == colonne_actuelle - 1)) {
                if (echiquier[rangee][colonne] != nullptr) {
                    if (echiquier[rangee][colonne]->get_couleur() == 0) {
                        return true;
                    }
                    else {
                        return false;
                    }
                }
                else {
                    return false;
                }
            }

            else {
                return false;
            }
        }
        else {
            if (rangee == rangee_actuelle - 1 && colonne == colonne_actuelle) {
                //set_pos(square);
                return true;
            }
            else if (rangee_actuelle == 6 && rangee == 4 && colonne == colonne_actuelle){
                if ( non_survol_pieces_deplacement(rangee_actuelle, rangee, colonne_actuelle, colonne, echiquier, SUD) ){
                    cout << "ok" << endl;
                    //set_pos(square);
                    return true;
                }
                else {
                    cout << "pas ok" << endl;
                    return false;
                }
            }

            else if (rangee == rangee_actuelle -1 && (colonne == colonne_actuelle - 1 || colonne == colonne_actuelle + 1)) {
                if (echiquier[rangee][colonne] != nullptr) {
                    if (echiquier[rangee][colonne]->get_couleur() == 1) {
                        //set_pos(square);
                        return true;
                    }
                    else {
                        return false;
                    }
                }
                else {
                    return false;
                }
            }

            else {
                return false;
            }
        }
    }

    void Pion::remplissage_coups_a_tester_pat(vector <Square> &coups_a_tester, Piece*** echiquier) {
        int rangee = this->square_.getRangee();
        int colonne = this->square_.getColonne();
        int direction;

        switch(this->get_couleur()){
            case 0 : //pion noir
                direction = -1;
                break;
            case 1 : //pion blanc
                direction = 1;
                break;
        }

        Square coup(rangee+direction, colonne);
        if (coup.existe()) {
            if (echiquier[rangee+direction][colonne] == nullptr){
                coups_a_tester.push_back(coup);
            }
        }

        coup.setSquare(rangee+direction, colonne+1);
        if (coup.existe()){
            if ( (echiquier[rangee+direction][colonne+1] != nullptr) && (echiquier[rangee+direction][colonne+1]->get_couleur() != this->couleur) ){
                coups_a_tester.push_back(coup);
            }
        }

        coup.setSquare(rangee+direction, colonne-1);
        if (coup.existe()){
            if ( (echiquier[rangee+direction][colonne-1] != nullptr) && (echiquier[rangee+direction][colonne-1]->get_couleur() != this->couleur) ){
                coups_a_tester.push_back(coup);
            }
        }
        return;

    }