#include <iostream>
#include <vector>
#include <string>
#include "../include/piece.h"
#include "../include/echiquier.h"


/**
* @file echiquier.cc : contient les fonctions relatives à l'échiquier
*/     
    
    Piece*** Echiquier::get_echiquier() {
        return this->echiquier;
    }

    Piece* Echiquier::getPiece(Square square) {
        int rangee = square.getRangee();
        int colonne = square.getColonne();
        return echiquier[rangee][colonne];
    }

    Piece* Echiquier::getPiece(int rangee, int colonne) {
        return echiquier[rangee][colonne];
    }

    void Echiquier::alloc_mem_echiquier() {
        echiquier = new Piece**[NBCOL];
        for (int i=0; i<NBCOL; i++) {
            echiquier[i] = new Piece*[NBCOL];
            for (int j=0; j<NBCOL; j++) {
                echiquier[i][j] = nullptr;
            }
        }

        for (int i=0; i<NBCOL; i++) {
            pionsb.push_back(nullptr);
            pionsn.push_back(nullptr);
            piecesb.push_back(nullptr);
            piecesn.push_back(nullptr);
        }

    }

    void Echiquier::promotion(Piece* &piece, Square square) {
        // transforme un pion en une pièce de la couleur de la promotion
        // et met à jour les vecteurs piecesb, piecesn, pionsb, pionsn
        // et le tableau echiquier
        int rangee = square.getRangee();
        int colonne = square.getColonne();
        if (rangee == 7 ) { //si la pièce arrive sur la dernière ligne (on sait déjà que c'est un pion, donc on sait que c'est une promotion)
            mort_piece(piece);
            delete(piece);
            piece = nullptr;
            string squareString = square.to_string();
            std::cout << "Q, N, R, B ? " << std::endl;
            char choix;
            std::cin >> choix;
            switch (choix) {
                case 'Q':
                    piece = new Dame(Blanc,"\u265B", square);
                    break;
                case 'N':
                    piece = new Cavalier(Blanc,"\u265E", square);
                    break;
                case 'R':
                    piece = new Tour(Blanc,"\u265C", square);
                    break;
                case 'B':
                    piece = new Fou(Blanc,"\u265D", square);
                    break;
                default:
                    std::cout << "Choix invalide" << std::endl;
                    return;
            }
            piecesb.push_back(piece);
        }
        else if (rangee == 0) {
            mort_piece(piece);
            delete(piece);
            piece = nullptr;
            string squareString = square.to_string();
            std::cout << "Q, N, R, B ? " << std::endl;
            char choix;
            std::cin >> choix;
            switch (choix) {
                case 'Q':
                    piece = new Dame(Noir,"\u2655", square);
                    break;
                case 'N':
                    piece = new Cavalier(Noir,"\u2658", square);
                    break;
                case 'R':
                    piece = new Tour(Noir,"\u2656", square);
                    break;
                case 'B':
                    piece = new Fou(Noir,"\u2657", square);
                    break;
                default:
                    std::cout << "Choix invalide" << std::endl;
                    return;
            }
            piecesn.push_back(piece);
        }
        else {
            return;
        }
        pose_piece(piece, square);


        
        echiquier[rangee][colonne] = piece;

        return;
    }

    void Echiquier::pose_piece(Piece* piece, Square square) {

        if (piece == nullptr) {
            std::cout << "Piece inexistante" << std::endl;
            return;
        }

        int rangee = square.getRangee();
        int colonne = square.getColonne();
        if (echiquier[rangee][colonne] != nullptr) {
            string squareString = square.to_string();
            std::cout << "Case " << squareString << " occupée" << std::endl;
            return;
        }
        echiquier[rangee][colonne] = piece;

        return;
    }

    void Echiquier::depart_piece(Square square) {

        int rangee = square.getRangee();
        int colonne = square.getColonne();
        if (echiquier[rangee][colonne] == nullptr) {
            string squareString = square.to_string();
            std::cout << "Case " << squareString << " vide" << std::endl;
            return;
        }
        echiquier[rangee][colonne] = nullptr;

        return;
    }

    void Echiquier::mort_piece(Piece *piece){

        if (piece == nullptr) {
            std::cout << "Piece inexistante" << std::endl;
            return;
        }

        int rangee = piece->get_pos().getRangee();
        int colonne = piece->get_pos().getColonne();

        if (piece->get_couleur() == Blanc) {//blanc
            if (piece->get_nom() == "\u265F") {//pion blanc
                for (unsigned int i=0; i<pionsb.size(); i++) {
                    if (pionsb[i] == piece) {
                        //supprimer la pièce du vecteur pionsb avec erase
                        pionsb.erase(pionsb.begin()+i);
                        break;
                    }
                }
            }
            else { //pièce blanche autre que pion
                for (unsigned int i=0; i<piecesb.size(); i++) {
                    if (piecesb[i] == piece) {
                        //supprimer la pièce du vecteur piecesb avec erase
                        piecesb.erase(piecesb.begin()+i);
                        break;
                    }
                }
            }
        }
        else {
            if (piece->get_nom() == "\u2659") { //pion noir
                for (unsigned int i=0; i<pionsn.size(); i++) {
                    if (pionsn[i] == piece) {
                        //supprimer la pièce du vecteur pionsn avec erase
                        pionsn.erase(pionsn.begin()+i);
                        break;
                    }
                }
            }
            else { //pièce noire autre que pion
                for (unsigned int i=0; i<piecesn.size(); i++) {
                    if (piecesn[i] == piece) {
                        //supprimer la pièce du vecteur piecesn avec erase
                        piecesn.erase(piecesn.begin()+i);
                        break;
                    }
                }
            }
        }
        echiquier[rangee][colonne] = nullptr;
        return;
        
    }

    void Echiquier::mort_piece(Square square) {
        // met à jour les vecteurs piecesb, piecesn, pionsb, pionsn
        // et le tableau echiquier
        int rangee = square.getRangee();
        int colonne = square.getColonne();
        if (echiquier[rangee][colonne] == nullptr) {
            string squareString = square.to_string();
            std::cout << "Case " << squareString << " vide" << std::endl;
            return;
        }
        Piece* piece = echiquier[rangee][colonne];
        mort_piece(piece);
    }

    void Echiquier::resurrection_piece(Piece *piece) {

        Square case_(0,0);
        case_.setSquare(piece->get_pos());
        int rangee = case_.getRangee();
        int colonne = case_.getColonne();

        if (piece->get_couleur() == Blanc) {//blanc
            if (piece->get_nom() == "\u265F") {//pion blanc
                pionsb.push_back(piece);
            }
            else { //pièce blanche autre que pion
                piecesb.push_back(piece);
            }
        }
        else {
            if (piece->get_nom() == "\u2659") { //pion noir
                pionsn.push_back(piece);
            }
            else { //pièce noire autre que pion
                piecesn.push_back(piece);
            }
        }
        echiquier[rangee][colonne] = piece;
        return;

    }

/*
*  Fonction qui effectue un coup sur l'échiquier
*  origine : case de départ du coup
*  destination : case d'arrivée du coup
*  sauvegarde_piece_mangee : pointeur vers la pièce mangée par le coup (nullptr si aucune pièce mangée)
*/
    void Echiquier::effectuer_coup(Square origine, Square destination, Piece* &sauvegarde_piece_mangee) {
        int rangee(origine.getRangee());
        int colonne(origine.getColonne());

        Piece* piece = echiquier[rangee][colonne];
        if (piece == nullptr) {
            std::cout << "Case vide" << std::endl;
            return;
        }
        Piece *piece_mangee = echiquier[destination.getRangee()][destination.getColonne()];
        if (piece_mangee != nullptr) {
            mort_piece(piece_mangee);
            sauvegarde_piece_mangee = piece_mangee;
        }
        piece -> set_pos(destination);
        pose_piece(piece, destination);
        depart_piece(origine);

        return;
        
    }

    void Echiquier::annuler_coup(Square origine, Square destination, Piece* &sauvegarde_piece_mangee) {

        Piece* piece = echiquier[destination.getRangee()][destination.getColonne()];
        if (piece == nullptr) {
            std::cout << "Case vide" << std::endl;
            return;
        }

        piece->set_pos(origine);
        pose_piece(piece, origine);
        depart_piece(destination);

        if (sauvegarde_piece_mangee != nullptr) {
            Piece *piece_mangee = sauvegarde_piece_mangee;
            resurrection_piece(piece_mangee);
        }

        sauvegarde_piece_mangee = nullptr;

        return;
        
    }


    bool Echiquier::nom_correspondant_piece(Piece *piece, string &nom) {
        if (piece == nullptr) {
            return false;
        }
        if (piece->get_nom() == nom) {
            return true;
        }
        return false;
    }



    bool Echiquier::case_attaquee_par_pion(Square case_, unsigned int couleur) {
        // retourne true si la case est attaquée par un pion de la couleur opposée
        // et false sinon
        int colonne = case_.getColonne();
        int rangee = case_.getRangee();

        int rangee_scannee;
        string nom_pion_ennemi;
        string &nom_pion_ennemi_ref = nom_pion_ennemi;
        Piece* pion_ennemi_potentiel = nullptr;

        switch (couleur){
            case Blanc:
                nom_pion_ennemi = "\u2659";
                if (rangee == 7 || rangee == 6){ //une case de la 8è ou 7è rangée ne peut pas être attaquée par un pion noir
                    return false;
                }
                rangee_scannee = rangee + 1;
                break;
            case Noir:
                nom_pion_ennemi = "\u265F";
                if (rangee == 0 || rangee == 1){ //et inversement
                    return false;
                }
                rangee_scannee = rangee - 1;
                break;
        }

        switch (colonne){
            case 0:
                pion_ennemi_potentiel = echiquier[rangee_scannee][colonne+1];
                if (nom_correspondant_piece (pion_ennemi_potentiel, nom_pion_ennemi_ref)){
                    return true;
                }
                break;
            case 7:
                pion_ennemi_potentiel = echiquier[rangee_scannee][colonne-1];
                if (nom_correspondant_piece (pion_ennemi_potentiel, nom_pion_ennemi_ref)){
                    return true;
                }
                break;
            default:
                pion_ennemi_potentiel = echiquier[rangee_scannee][colonne+1];
                if (nom_correspondant_piece (pion_ennemi_potentiel, nom_pion_ennemi_ref)){
                    return true;
                }
                pion_ennemi_potentiel = echiquier[rangee_scannee][colonne-1];
                if (nom_correspondant_piece (pion_ennemi_potentiel, nom_pion_ennemi_ref)){
                    return true;
                }
                break;
        }

        return false;

        }


    bool Echiquier::case_attaquee_par_piece(Square case_, unsigned int couleur) {

            switch(couleur){
            case Blanc:
                for (unsigned int i=0; i<piecesn.size(); i++){

                    if (piecesn[i]->deplacement(case_ , this->echiquier) ){
                        return true;
                    }
                }
                break;
            case Noir:
                for (unsigned int i=0; i<piecesb.size(); i++){

                    if (piecesb[i]->deplacement(case_, this->echiquier) ){
                        return true;
                    }
                }
                break;
        }
        return false;
    }
        
    Piece* Echiquier::case_attaquee_par_pion_attaquant(Square case_, unsigned int couleur) {
        // si la case est attaquée par un pion de la couleur opposée, renvoie le pion attaquant
        // et nullptr sinon
        int colonne = case_.getColonne();
        int rangee = case_.getRangee();

        int rangee_scannee;
        string nom_pion_ennemi;
        string &nom_pion_ennemi_ref = nom_pion_ennemi;
        Piece* pion_ennemi_potentiel = nullptr;

        switch (couleur){
            case Blanc:
                nom_pion_ennemi = "\u2659";
                if (rangee == 7 || rangee == 6){ //une case de la 8è ou 7è rangée ne peut pas être attaquée par un pion noir
                    return nullptr;
                }
                rangee_scannee = rangee + 1;
                break;
            case Noir:
                nom_pion_ennemi = "\u265F";
                if (rangee == 0 || rangee == 1){ //et inversement
                    return nullptr;
                }
                rangee_scannee = rangee - 1;
                break;
        }

        switch (colonne){
            case 0:
                pion_ennemi_potentiel = echiquier[rangee_scannee][colonne+1];
                if (nom_correspondant_piece (pion_ennemi_potentiel, nom_pion_ennemi_ref)){
                    return pion_ennemi_potentiel;
                }
                break;
            case 7:
                pion_ennemi_potentiel = echiquier[rangee_scannee][colonne-1];
                if (nom_correspondant_piece (pion_ennemi_potentiel, nom_pion_ennemi_ref)){
                    return pion_ennemi_potentiel;
                }
                break;
            default:
                pion_ennemi_potentiel = echiquier[rangee_scannee][colonne+1];
                if (nom_correspondant_piece (pion_ennemi_potentiel, nom_pion_ennemi_ref)){
                    return pion_ennemi_potentiel;
                }
                pion_ennemi_potentiel = echiquier[rangee_scannee][colonne-1];
                if (nom_correspondant_piece (pion_ennemi_potentiel, nom_pion_ennemi_ref)){
                    return pion_ennemi_potentiel;
                }
                break;
        }

        return nullptr;
    }

    void Echiquier::remplissage_attaquants_roi_pion_potentiel(unsigned int couleur, vector <Piece*> &pieces_attaquantes) {
        Square case_roi(0,0);
        Piece* pion_attaquant = nullptr;

        switch (couleur){
            case Blanc:
                case_roi.setSquare(piecesb[0]->get_pos());
                pion_attaquant = case_attaquee_par_pion_attaquant(case_roi, couleur);
                if (pion_attaquant != nullptr){
                    pieces_attaquantes.push_back(pion_attaquant);
                }
                break;
            case Noir:
                case_roi.setSquare(piecesn[0]->get_pos());
                pion_attaquant = case_attaquee_par_pion_attaquant(case_roi, couleur);
                if (pion_attaquant != nullptr){
                    pieces_attaquantes.push_back(pion_attaquant);
                }
                break;
        }
    }


    bool Echiquier::case_attaquee(Square case_, unsigned int couleur) {
        // retourne true si la case est attaquée par une pièce de la couleur opposée
        // et false sinon

        if (case_attaquee_par_pion(case_, couleur)){
            return true;
        }
        if (case_attaquee_par_piece(case_, couleur)){
            return true;
        }
        
        return false;
    }


    bool Echiquier::detection_echec_pion(unsigned int couleur){
        Square case_roi(0,0);
        
        switch (couleur){
            case Blanc:
                case_roi.setSquare(piecesb[0]->get_pos());
                return case_attaquee_par_pion(case_roi, Blanc);
                break;

            case Noir:
                case_roi.setSquare(piecesn[0]->get_pos());
                return case_attaquee_par_pion(case_roi, Noir);
                break;

        }

        return false;
    }

    void Echiquier::remplissage_attaquants_roi(unsigned int couleur, vector<Piece*> &pieces_attaquantes){
        Square case_roi = Square(0,0);
        Piece* pion_attaquant = nullptr;
        vector <Piece*> pieces_ennemies;

        switch (couleur){
            case Blanc:
                case_roi.setSquare(piecesb[0]->get_pos());
                pieces_ennemies = piecesn;
                break;
            case Noir:
                case_roi.setSquare(piecesn[0]->get_pos());
                pieces_ennemies = piecesb;
                break;

        }

        pion_attaquant = case_attaquee_par_pion_attaquant(case_roi, couleur);
        if (pion_attaquant != nullptr){
            pieces_attaquantes.push_back(pion_attaquant);
        }

        for (unsigned int i=0; i<pieces_ennemies.size(); i++){
            if (pieces_ennemies[i]->deplacement(case_roi, this->echiquier)){
                pieces_attaquantes.push_back(pieces_ennemies[i]);
            }
        }

        return;
    }


    bool Echiquier::detection_echec(unsigned int couleur){

        switch (couleur){
            case Blanc:
                return case_attaquee(piecesb[0]->get_pos(), Blanc);
                break;
            case Noir:
                return case_attaquee(piecesn[0]->get_pos(), Noir);
                break;
        }
        return false; //normalement inutile, pour compilation

    }



    bool Echiquier::coup_roi_disponible (unsigned int couleur){
        Square case_roi(0,0);
        Piece* roi = nullptr;

        switch (couleur){
            case Blanc:
                roi = piecesb[0];
                case_roi.setSquare(roi->get_pos());
                break;
            case Noir:
                roi = piecesn[0];
                case_roi.setSquare(roi->get_pos());
                break;
        }

        int colonne = case_roi.getColonne();
        int rangee = case_roi.getRangee();

        vector<Square> cases_potentielles;
        cases_potentielles.push_back(Square(rangee-1, colonne-1));
        cases_potentielles.push_back(Square(rangee-1, colonne));
        cases_potentielles.push_back(Square(rangee-1, colonne+1));
        cases_potentielles.push_back(Square(rangee, colonne-1));
        cases_potentielles.push_back(Square(rangee, colonne+1));
        cases_potentielles.push_back(Square(rangee+1, colonne-1));
        cases_potentielles.push_back(Square(rangee+1, colonne));
        cases_potentielles.push_back(Square(rangee+1, colonne+1));


        for(unsigned int i=0; i<cases_potentielles.size(); i++){ //premier tri des cases potentielles (cases hors échiquier)

            if (cases_potentielles[i].getColonne() < 0 || cases_potentielles[i].getColonne() > 7 || cases_potentielles[i].getRangee() < 0 || cases_potentielles[i].getRangee() > 7){
                //retirer la case du vecteur
                cases_potentielles.erase(cases_potentielles.begin()+i);
                i--;
            }
        }
        cout << "tri" << endl;
        for(unsigned int i=0; i<cases_potentielles.size(); i++){ //deuxième tri des cases potentielles (cases occupées par une pièce de la même couleur)
            if ( echiquier[cases_potentielles[i].getRangee()][cases_potentielles[i].getColonne()] != nullptr){
                if (echiquier[cases_potentielles[i].getRangee()][cases_potentielles[i].getColonne()]->get_couleur() == couleur){
                    cases_potentielles.erase(cases_potentielles.begin()+i);
                    i--;
                }
            }
        }

        for(unsigned int i=0; i<cases_potentielles.size(); i++){ //troisième tri des cases potentielles (cases attaquées par une pièce adverse)
            cout << "case potentielle roi : " << cases_potentielles[i].getRangee() << " " << cases_potentielles[i].getColonne() << endl;
            if (echiquier[cases_potentielles[i].getRangee()][cases_potentielles[i].getColonne()] != nullptr){ //si la case est occupée par une pièce adverse
                Piece* sauvegarde = echiquier[cases_potentielles[i].getRangee()][cases_potentielles[i].getColonne()];
                Piece* &ref_sauvegarde = sauvegarde;

                effectuer_coup(case_roi, cases_potentielles[i], ref_sauvegarde);
                
                if (!detection_echec(couleur)){
                    annuler_coup(case_roi, cases_potentielles[i], ref_sauvegarde);
                    return true;
                }
                annuler_coup(case_roi, cases_potentielles[i], ref_sauvegarde);
            }
            else if (!case_attaquee(cases_potentielles[i], couleur)){ //case vide et non attaquée
                return true;
            }
        }

        return false;

    }


    bool Echiquier::prise_pour_parer_echec_possible(Piece* attaquant, unsigned int couleur){
        
        Square case_attaquant = attaquant->get_pos();
        Square case_depart;
        vector <Piece*> pions_alliés;
        vector <Piece*> pieces_alliées;

        switch(couleur){
            case Blanc:
                pions_alliés = pionsb;
                pieces_alliées = piecesb;
                break;
            case Noir:
                pions_alliés = pionsn;
                pieces_alliées = piecesn;
                break;
        }

        for (unsigned int i = 0; i<pions_alliés.size() ; i++){
            if (pions_alliés[i]->deplacement(case_attaquant, this->echiquier)){
                Piece *sauvegarde_attaquant = attaquant;
                mort_piece(attaquant);
                case_depart.setSquare ( pions_alliés[i]->get_pos() );

                pions_alliés[i]->set_pos(case_attaquant);
                depart_piece(case_depart);
                pose_piece(pions_alliés[i], case_attaquant);

                if (!detection_echec(couleur)){
                    pions_alliés[i]->set_pos(case_depart);
                    depart_piece(case_attaquant);
                    pose_piece(pions_alliés[i], case_depart);
                    resurrection_piece(sauvegarde_attaquant);
                    return true;
                }
                pions_alliés[i]->set_pos(case_depart);
                depart_piece(case_attaquant);
                pose_piece(pions_alliés[i], case_depart);
                resurrection_piece(sauvegarde_attaquant);

            }
        }

        for (unsigned int i = 0; i<pieces_alliées.size() ; i++){
            if (pieces_alliées[i]->deplacement(case_attaquant, this->echiquier)){
                Piece *sauvegarde_attaquant = attaquant;
                mort_piece(attaquant);
                case_depart.setSquare (pieces_alliées[i]->get_pos());

                pieces_alliées[i]->set_pos(case_attaquant);
                depart_piece(case_depart);
                pose_piece(pieces_alliées[i], case_attaquant);

                if (!detection_echec(couleur)){
                    pieces_alliées[i]->set_pos(case_depart);
                    depart_piece(case_attaquant);
                    pose_piece(pieces_alliées[i], case_depart);
                    resurrection_piece(sauvegarde_attaquant);
                    return true;
                }
                pieces_alliées[i]->set_pos(case_depart);
                depart_piece(case_attaquant);
                pose_piece(pieces_alliées[i], case_depart);
                resurrection_piece(sauvegarde_attaquant);

            }
        }
        return false;

    }


    bool Echiquier::blocage_echec_possible(Square case_, unsigned int couleur){
        vector <Piece*> pieces_alliées;
        vector <Piece*> pions_alliés;
        Square case_depart;

        switch(couleur){
            case Blanc:
                pieces_alliées = piecesb;
                pions_alliés = pionsb;
                break;
            case Noir:
                pieces_alliées = piecesn;
                pions_alliés = pionsn;
                break;
        }

        for (unsigned int i = 0; i<pions_alliés.size() ; i++){
            if (pions_alliés[i]->deplacement(case_, this->echiquier)){
                case_depart.setSquare( pions_alliés[i]->get_pos() );

                pions_alliés[i]->set_pos(case_);
                depart_piece(case_depart);
                pose_piece(pions_alliés[i], case_);

                if (!detection_echec(couleur)){
                    pions_alliés[i]->set_pos(case_depart);
                    depart_piece(case_);
                    pose_piece(pions_alliés[i], case_depart);
                    cout << pieces_alliées[i]->get_nom() << "peut parer l'échec" << endl;
                    return true;
                }
                pions_alliés[i]->set_pos(case_depart);
                depart_piece(case_);
                pose_piece(pions_alliés[i], case_depart);

            }
        }

        for (unsigned int i = 0; i<pieces_alliées.size() ; i++){
            if (pieces_alliées[i]->deplacement(case_, this->echiquier)){
                case_depart.setSquare ( pieces_alliées[i]->get_pos() );

                pieces_alliées[i]->set_pos(case_);
                depart_piece(case_depart);
                pose_piece(pieces_alliées[i], case_);

                if (!detection_echec(couleur)){
                    pieces_alliées[i]->set_pos(case_depart);
                    depart_piece(case_);
                    pose_piece(pieces_alliées[i], case_depart);
                    cout << pieces_alliées[i]->get_nom() << "peut parer l'échec" << endl;
                    return true;
                }
                pieces_alliées[i]->set_pos(case_depart);
                depart_piece(case_);
                pose_piece(pieces_alliées[i], case_depart);

            }
        }
        return false;
    }

/*
* @brief Cette fonction permet de savoir si un roi est en échec et mat après un coup
* Elle renvoie true si le roi est en échec et mat, false sinon
* Elle teste d'abord si le roi peut se déplacer, si oui, il n'est pas en échec et mat
* Elle teste ensuite si un seul attaquant est présent, si oui, il s'agit d'un échec simple
* En cas de double échec, le roi est forcément mat (on ne peut pas bloquer deux attaquants)
* Si le roi est en échec simple, on teste si un de ses alliés peut éliminer l'attaquant (si oui pas mat)
* Enfin, on teste si un de ses alliés peut bloquer l'échec en s'interposant entre le roi et l'attaquant
* S'il n'est si possible de bouger le roi, ni d'éliminer l'attaquant, ni de bloquer l'échec, le roi est en échec et mat
* @ param couleur : la couleur du roi
* @ return true si le roi est en échec et mat, false sinon
*/

    bool Echiquier::detection_echec_et_mat(unsigned int couleur){

        bool coup_roi_dispo = coup_roi_disponible(couleur);
        if (coup_roi_dispo){
            cout << "Pas mat car coup roi disponible" << endl;
            return false;
        }

        else {
            cout << "Pas de coup de roi jouable" << endl;
            vector<Piece*> pieces_pouvant_manger_roi_adverse = vector<Piece*>();
            vector<Piece*> &reference = pieces_pouvant_manger_roi_adverse;

            remplissage_attaquants_roi(couleur, reference);
            if (reference.size() == 1) { //si echec simple

                Piece *pi = reference[0];
                TypePiece type = pi->type;
                Square case_attaquant = pi->get_pos();

                if (case_attaquee(case_attaquant, !couleur)) { //si l'attaquant est attaqué, l'échec peut être paré en le prenant (si la prise est légale, ie si le roi n'est pas en échec après la prise)
                    //cout << "Echec simple parable par prise de la pièce attaquante" << endl;
                    if (prise_pour_parer_echec_possible(pi, couleur)){
                        cout << "Echec simple parable par prise de la pièce attaquante" << endl;
                        return false;
                    }
                    cout << "Echec simple non parable par prise de la pièce attaquante car mettrait en échec" << endl;
                }

                else {
                    cout << "Attaquant non éliminable" << endl;
                }

                Square case_roi;
                if (couleur == Blanc){
                    case_roi.setSquare ( piecesb[0]->get_pos() );
                }
                else{
                    case_roi.setSquare ( piecesn[0]->get_pos() );
                }

                cout << pi->get_nom() << " peut manger votre roi" << endl;

                vector <Square> cases_pour_parer_echec;


                if (type == DAME || type == TOUR || type == FOU){
                    int colonne_attaquant = case_attaquant.getColonne();
                    int rangee_attaquant = case_attaquant.getRangee();
                    int colonne_roi = case_roi.getColonne();
                    int rangee_roi = case_roi.getRangee();

                    int increment_colonne = 0;
                    int increment_rangee = 0;

                    if (colonne_attaquant == colonne_roi){
                        if (rangee_attaquant < rangee_roi){
                            increment_colonne = 0;
                            increment_rangee = -1;
                            cout << "SUD" << endl;
                        }
                        else{
                            increment_colonne = 0;
                            increment_rangee = 1;
                            cout << "NORD" << endl;
                        }
                    }

                    else if (rangee_attaquant == rangee_roi){
                        if (colonne_attaquant > colonne_roi){
                            increment_colonne = 1;
                            increment_rangee = 0;
                            cout << "EST" << endl;
                        }
                        else{
                            increment_colonne = -1;
                            increment_rangee = 0;
                            cout << "OUEST" << endl;
                        }
                    }

                    else if (colonne_attaquant < colonne_roi){
                        if (rangee_attaquant < rangee_roi){
                            increment_colonne = -1;
                            increment_rangee = -1;
                            cout << "SUD_OUEST" << endl;
                        }
                        else{
                            increment_colonne = -1;
                            increment_rangee = 1;
                            cout << "NORD_OUEST" << endl;
                        }
                    }

                    else if (colonne_attaquant > colonne_roi){
                        if (rangee_attaquant < rangee_roi){
                            increment_colonne = 1;
                            increment_rangee = -1;
                            cout << "SUD_EST" << endl;
                        }
                        else{
                            increment_colonne = 1;
                            increment_rangee = 1;
                            cout << "NORD_EST" << endl;
                        }
                    }

                    int colonne = colonne_roi + increment_colonne;
                    int rangee = rangee_roi + increment_rangee;

                    while (colonne != colonne_attaquant || rangee != rangee_attaquant){
                        Square case_temp(rangee, colonne);
                        cases_pour_parer_echec.push_back(case_temp);
                        colonne += increment_colonne;
                        rangee += increment_rangee;
                    }

                    for (unsigned int i = 0; i < cases_pour_parer_echec.size(); i++){
                        cout << cases_pour_parer_echec[i].getRangee() << " " << cases_pour_parer_echec[i].getColonne() << endl;
                    }

                    for (unsigned int i = 0; i < cases_pour_parer_echec.size(); i++){
                        if (blocage_echec_possible(cases_pour_parer_echec[i], couleur)){
                            cout << "Echec simple parable par blocage" << endl;
                            return false;
                        }
                    }


                }

                else {
                    return true; // si l'attaquant est un cavalier ou un pion, le roi ne peut pas le bloquer
                }


            }

            else if (pieces_pouvant_manger_roi_adverse.size() == 2){
                return true; // si double échec, roi est obligé de bouger (donc si il ne peut pas bouger, c'est mat)
            }
        }

        return true;
    }


/**
*  Fonction qui vérifie s'il y a un pat après un coup joué
*  @param couleur : la couleur du joueur qui vient de jouer
*  @return true si le joueur est en pat, false sinon

*  L'idée de cette fonction est que pour qu'une pièce soit en position de pat, il suffit qu'elle ne puisse pas bouger dans aucune direction
*  Ainsi pour une tour par exemple, seuls 4 coups sont à tester : d'une case vers le nord, le sud, l'est et l'ouest
*  Si aucun de ces coups n'est légal, alors la tour est forcément en pat (on pourrait le démontrer mathématiquement)
        cette méthode permet de gérer correctement le cas où, par exemple, une tour est clouée par une autre tour, et donc pourrait potentiellement bouger
        quand même (dans sa direction)
*  Similairement, il faut tester 4 coups pour un fou, 8 coups pour une dame, 3 coups pour un pion, tous les coups d'un roi
*  (Pour un cavalier, si plusieurs coups étaient légaux sans vérifier les échecs, il suffit de vérifier qu'il n'y a pas d'échec après un seul)
        on est alors sur que le cavalier est cloué et donc en pat

*  Ces coups sont créés par la pièce elle-même, et un premier filtrage est réalisé (celui des cases en dehors de l'échiquier)
        puis un second filtrage est réalisé (celui des cases occupées par des pièces alliées)
*/
    bool Echiquier::detection_pat(unsigned int couleur) {
        vector <Piece *> pieces_alliees;
        vector <Piece *> pions_alliés;

        switch (couleur){
            case Blanc:
                pieces_alliees = piecesb;
                pions_alliés = pionsb;
                break;
            case Noir:
                pieces_alliees = piecesn;
                pions_alliés = pionsn;
                break;
        }

        for (unsigned int i = 0; i < pieces_alliees.size(); i++){
            Piece *piece = pieces_alliees[i];
            vector <Square> coups_a_tester;
            vector <Square> &coups_a_tester_ref = coups_a_tester;
            piece->remplissage_coups_a_tester_pat(coups_a_tester_ref, echiquier);

            for (unsigned int j = 0; j < coups_a_tester.size(); j++){
                Square case_testee = coups_a_tester[j];
                Square case_depart = piece->get_pos();

                Piece *sauvegarde_piece_mangee = nullptr;
                Piece* &sauvegarde_piece_mangee_ref = sauvegarde_piece_mangee;

                effectuer_coup(case_depart, case_testee, sauvegarde_piece_mangee_ref);
                if (!detection_echec(couleur)){
                    annuler_coup(case_depart, case_testee, sauvegarde_piece_mangee_ref);
                    return false;
                }
                annuler_coup(case_depart, case_testee, sauvegarde_piece_mangee_ref);
                
            }
        }

        for (unsigned int i = 0; i < pions_alliés.size(); i++){
            Piece *piece = pions_alliés[i];
            vector <Square> coups_a_tester;
            vector <Square> &coups_a_tester_ref = coups_a_tester;
            piece->remplissage_coups_a_tester_pat(coups_a_tester_ref, echiquier);

            for (unsigned int j = 0; j < coups_a_tester.size(); j++){
                Square case_testee = coups_a_tester[j];
                Square case_depart = piece->get_pos();

                Piece *sauvegarde_piece_mangee;
                Piece* &sauvegarde_piece_mangee_ref = sauvegarde_piece_mangee;

                effectuer_coup(case_depart, case_testee, sauvegarde_piece_mangee_ref);
                if (!detection_echec(couleur)){
                    annuler_coup(case_depart, case_testee, sauvegarde_piece_mangee_ref);
                    return false;
                }
                annuler_coup(case_depart, case_testee, sauvegarde_piece_mangee_ref);
                
            }
        }



        return true;
    }
    


    Echiquier::Echiquier () 
    {   

        alloc_mem_echiquier(); // --> alloue un tableau équivalent à un Piece *[8][8]
                            //     en initialisant les cases à nullptr 
                            //     et alloue des vecteurs piecesb, piecesn, pionsb
        // Constructeur (Couleur,nom_affiché, case, identifiant)
        piecesb[0] = new Roi     (Blanc,"\u265A",  Square(0,4));
        piecesb[1] = new Tour    (Blanc,"\u265C",  Square(0,0));
        piecesb[2] = new Cavalier(Blanc,"\u265E",  Square(0,1));
        piecesb[3] = new Fou     (Blanc,"\u265D",  Square(0,2));
        piecesb[4] = new Dame    (Blanc,"\u265B",  Square(0,3));
        piecesb[5] = new Fou     (Blanc,"\u265D",  Square(0,5));
        piecesb[6] = new Cavalier(Blanc,"\u265E",  Square(0,6));
        piecesb[7] = new Tour    (Blanc,"\u265C",  Square(0,7));

        piecesn[0] = new Roi     (Noir, "\u2654",  Square(7,4));
        piecesn[1] = new Tour    (Noir, "\u2656",  Square(7,0));
        piecesn[2] = new Cavalier(Noir, "\u2658",  Square(7,1));
        piecesn[3] = new Fou     (Noir, "\u2657",  Square(7,2));
        piecesn[4] = new Dame    (Noir, "\u2655",  Square(7,3));
        piecesn[5] = new Fou     (Noir, "\u2657",  Square(7,5));
        piecesn[6] = new Cavalier(Noir, "\u2658",  Square(7,6));
        piecesn[7] = new Tour    (Noir, "\u2656",  Square(7,7));

        // allocation des pions
        for (unsigned char i(0);i<NBCOL;i++) {
            pionsb[i] =  new Pion(Blanc, "\u265F", Square(1,i));
            pionsn[i] =  new Pion(Noir,  "\u2659", Square(6,i));
        }
        // Pose des pieces en position initiale
        // pose des pieces blanches
        for (unsigned char i(0);i<NBCOL;i++) {
            // met à jour le tableau echiquier, à la case donnée par 
            // la position courante de la pièce obtenue avec 
            // piecesb[i]->get_pos(),
            // avec le pointeur vers la pièce (piecesb[i])
            pose_piece(piecesb[i],piecesb[i]->get_pos());   
            pose_piece(pionsb[i],pionsb[i]->get_pos());
        }
        // pose des pieces noires
        for (unsigned char i(0);i<NBCOL;i++) {
            pose_piece(piecesn[i],piecesn[i]->get_pos());   
            pose_piece(pionsn[i],pionsn[i]->get_pos());
        }
    }

    void Echiquier::libere(vector<Piece*> vecteur){
        for (int i=vecteur.size() - 1; i>=0; i--) {
            if (vecteur[i] != nullptr) {
                delete vecteur[i];
            }
        }
        return;
    }

    Echiquier::~Echiquier () {

        libere(piecesb);
        libere(piecesn);
        libere(pionsb);
        libere(pionsn);

        for (int i = 0; i < 8; i++) {
            delete[] echiquier[i];
        }
        delete[] echiquier;
        return;
    }
    
    void Echiquier::affiche () const {

        string space5 = string(5,' ');
        cout << endl;
        cout << "     a     b     c     d     e     f     g     h    "<< endl;
        cout << "  +-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
        for (int i(NBCOL-1);i>=0;i--) {
                cout << i+1 << " "; // numérotation ligne dans affichage
                for (int j(0);j<NBCOL;j++) {
                        cout << "|" ;
                        if (echiquier[i][j]) { 
                            cout << "\u0020\u0020";  //U+0020 est un esapce utf-8 taille police
                            echiquier[i][j]-> affiche();
                            cout << "\u0020" << " ";
                        }
                        else 
                                cout << space5;  // 2 ascii spaces
                }
                cout << "|\n  +-----+-----+-----+-----+-----+-----+-----+-----+";
                cout << endl;
        }
}
    void Echiquier::deplace() {
        cout << "deplace" << endl;
    }


    string Echiquier::pgn_piece_name(string const name, bool view_pawn, bool view_color) {

        string psymb;
        if      (name=="\u2656") psymb="R";  // Rook W
        else if (name=="\u2658") psymb="N";  // Knight W
        else if (name=="\u2657") psymb="B";  // Bishop W
        else if (name=="\u2655") psymb="Q";  // Queen W
        else if (name=="\u2654") psymb="K";  // King W
        else if (name.rfind("\u2659",0)==0 && view_pawn) psymb= "P"; // Pawn W
        if (psymb.size()>0) { // one of the white piece has been found
                if (view_color)
                        return "b"+psymb;
                else
                        return psymb;
        } 
        if      (name=="\u265C") psymb= "R";  // Rook B
        else if (name=="\u265E") psymb= "N";  // Knight B
        else if (name=="\u265D") psymb= "B";  // Bishop B
        else if (name=="\u265B") psymb= "Q";  // Queen B
        else if (name=="\u265A") psymb= "K";  // King B
        else if (name.rfind("\u265F",0)==0 && view_pawn) psymb= "P"; // Pawn B
        if (psymb.size()>0) { // one of the black piece has been found
                if (view_color)
                        return "w"+psymb;
                else
                        return psymb;
        } 
        else return "";
    }

string Echiquier::canonical_position() {
    string output;
    for (size_t row(1); row<=8; row++){
            for (char col('a');col<='h';col++) {
                    Square square(col+to_string(row)); 
                    if (getPiece(square)!=nullptr)
                            // get pieces with theit PGN names, 
                            // true -> with P for pawns, true -> w/b for colors.
                            output += pgn_piece_name(getPiece(square)->get_nom(),true,true);
                    output += ",";
            }
    }
    return output;
    }