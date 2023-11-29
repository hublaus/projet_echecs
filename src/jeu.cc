#include "../include/jeu.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
*  @file jeu.cc : contient les fonctions relatives à la prise en passant, au jeu ainsi que le main global du programme
*/


Piece* Prise_en_passant::get_pion_pouvant_etre_pris_en_passant() {
    return this->pion_pouvant_etre_pris_en_passant;
}

Prise_en_passant::Prise_en_passant() : pion_pouvant_etre_pris_en_passant(nullptr) {}


bool Prise_en_passant::est_prise_en_passant(Square origine, Square destination){
    for (unsigned int i=0; i<prises_en_passant_possibles.size(); i++){
        if (prises_en_passant_possibles[i].origine.getRangee() == origine.getRangee() && prises_en_passant_possibles[i].origine.getColonne() == origine.getColonne() && prises_en_passant_possibles[i].destination.getRangee() == destination.getRangee() && prises_en_passant_possibles[i].destination.getColonne() == destination.getColonne()){
            return true;
        }
    }

    return false;
}


void Prise_en_passant::remplissage_prise_en_passant(bool tour_des_blancs, int colonne, Piece ***echiquier){
    int rangee (0);
    int direction (0); //direction de la prise en passant (si pion blanc vient de bouger, vers le sud donc -1)

    switch (tour_des_blancs){
        case true : 
            rangee = 3;
            direction = -1;
            break;
        case false :
            rangee = 4;
            direction = 1;
            break;
    }

    switch (colonne){
        case 0:
            if (echiquier[rangee][1] != nullptr){
                if (echiquier[rangee][1]->type == PION && echiquier[rangee][1]->get_couleur() != tour_des_blancs){
                    prises_en_passant_possibles.push_back({Square(rangee, 1), Square(rangee + direction, 0)});
                    cout << "prise en passant possible" << endl;
                    cout << "origine : " << prises_en_passant_possibles[0].origine.getRangee() << " " << prises_en_passant_possibles[0].origine.getColonne() << endl;
                    cout << "destination : " << prises_en_passant_possibles[0].destination.getRangee() << " " << prises_en_passant_possibles[0].destination.getColonne() << endl;
                }
            }
            break;
        
        case 7:
            if (echiquier [rangee][6] != nullptr){
                if (echiquier[rangee][6]->type == PION && echiquier[rangee][6]->get_couleur() != tour_des_blancs){
                    prises_en_passant_possibles.push_back({Square(rangee, 6), Square(rangee + direction, 7)});
                    cout << "prise en passant possible" << endl;
                    cout << "origine : " << prises_en_passant_possibles[0].origine.getRangee() << " " << prises_en_passant_possibles[0].origine.getColonne() << endl;
                    cout << "destination : " << prises_en_passant_possibles[0].destination.getRangee() << " " << prises_en_passant_possibles[0].destination.getColonne() << endl;
                }
            }
            break;
        
        default :

            if (echiquier[rangee][colonne - 1] != nullptr){
                if (echiquier[rangee][colonne - 1]->type == PION && echiquier[rangee][colonne - 1]->get_couleur() != tour_des_blancs){
                    prises_en_passant_possibles.push_back({Square(rangee, colonne - 1), Square(rangee + direction, colonne)});
                    cout << "prise en passant possible" << endl;
                }
            }

            if (echiquier[rangee][colonne + 1] != nullptr){
                if (echiquier[rangee][colonne + 1]->type == PION && echiquier[rangee][colonne + 1]->get_couleur() != tour_des_blancs){
                    prises_en_passant_possibles.push_back({Square(rangee, colonne + 1), Square(rangee + direction, colonne)});
                    cout << "prise en passant possible" << endl;
                }
            }
        break; 
    }

    if (prises_en_passant_possibles.size() != 0){
        pion_pouvant_etre_pris_en_passant = echiquier[rangee][colonne];
    }

return;
}

void Prise_en_passant::nettoyage(){
    prises_en_passant_possibles.clear();
    pion_pouvant_etre_pris_en_passant = nullptr;
    return;
}


Jeu::Jeu() : tour_des_blancs(true), compteur_coups(0), resultat_partie(PAS_DEFINI), resultat_coup(COUP_NORMAL), stop(false), sauvegarde_piece_mangee(nullptr) {
}

void Jeu::set_stop(bool stop_){
    stop = stop_;
}

bool Jeu::get_stop(){
    return stop;
}


bool Jeu::roque_possible(bool petit_cote, unsigned char couleur, Echiquier &echiquier){

    Piece *roi_;
    Piece *tour_;

    switch (couleur){
        case 1 : //blanc
            roi_ = echiquier.getPiece(Square(0, 4));

            switch (petit_cote){
                case true: //petit roque blanc
                    tour_ = echiquier.getPiece(Square(0, 7));
                    if (echiquier.getPiece(Square(0, 5)) != nullptr || echiquier.getPiece(Square(0, 6)) != nullptr){
                        cout << "une case du roque est occupee" << endl;
                        return false;
                    }

                    else if (tour_ == nullptr || roi_ == nullptr
                        || tour_->get_nom() != "\u265C" || roi_->get_nom() != "\u265A"){
                            cout << "tour et/ou roi manquant" << endl;
                            return false;
                        }
                    if (tour_->a_deja_bouge_fonction() || roi_->a_deja_bouge_fonction()){
                        cout << "tour et/ou roi ont deja bouge" << endl;
                        return false;
                    }
                    if(this->echiquier.case_attaquee(Square(0, 5), 1) || this->echiquier.case_attaquee(Square(0, 6), 1) || this->echiquier.case_attaquee(Square(0, 4), 1)){
                        cout << "une case du roque est attaquee ou le roi est en échec" << endl;
                        return false;
                    }
                    else{
                        return true;
                    }
                    break;

                case false: //grand roque blanc
                    tour_ = echiquier.getPiece(Square(0, 0));
                    if (echiquier.getPiece(Square(0, 1)) != nullptr || echiquier.getPiece(Square(0, 2)) != nullptr || echiquier.getPiece(Square(0, 3)) != nullptr){
                        cout << "une case du roque est occupee" << endl;
                        return false;
                    }

                    else if (tour_ == nullptr || roi_ == nullptr
                        || tour_->get_nom() != "\u265C" || roi_->get_nom() != "\u265A"){
                            cout << "tour et/ou roi manquant" << endl;
                            return false;
                        }
                    if (tour_->a_deja_bouge_fonction() || roi_->a_deja_bouge_fonction()){
                        cout << "tour et/ou roi ont deja bouge" << endl;
                        return false;
                    }
                    if(this->echiquier.case_attaquee(Square(0, 1), 1) || this->echiquier.case_attaquee(Square(0, 2), 1) || this->echiquier.case_attaquee(Square(0, 3), 1) || this->echiquier.case_attaquee(Square(0, 4), 1)){
                        cout << "une case du roque est attaquee ou le roi est en échec" << endl;
                        return false;
                    }
                    else{
                        return true;
                    }
                    break;
            }

        case false: //cas noir
            roi_ = echiquier.getPiece(Square(7, 4));

            switch(petit_cote){
                case true: //petit roque noir
                    tour_ = echiquier.getPiece(Square(7, 7));
                    if (echiquier.getPiece(Square(7, 5)) != nullptr || echiquier.getPiece(Square(7, 6)) != nullptr){
                        cout << "une case du roque est occupee" << endl;
                        return false;
                    }

                    else if (tour_ == nullptr || roi_ == nullptr
                        || tour_->get_nom() != "\u2656" || roi_->get_nom() != "\u2654"){
                            cout << "tour et/ou roi manquant" << endl;
                            return false;
                        }
                    if (tour_->a_deja_bouge_fonction() || roi_->a_deja_bouge_fonction()){
                        cout << "tour et/ou roi ont deja bouge" << endl;
                        return false;
                    }
                    if(this->echiquier.case_attaquee(Square(7, 5), 0) || this->echiquier.case_attaquee(Square(7, 6), 0) || this->echiquier.case_attaquee(Square(7, 4), 0)){
                        cout << "une case du roque est attaquee ou le roi est en échec" << endl;
                        return false;
                    }
                    else{
                        return true;
                    }
                    break;

                case false: //grand roque noir
                    tour_ = echiquier.getPiece(Square(7, 0));
                    if (echiquier.getPiece(Square(7, 1)) != nullptr || echiquier.getPiece(Square(7, 2)) != nullptr || echiquier.getPiece(Square(7, 3)) != nullptr){
                        cout << "une case du roque est occupee" << endl;
                        return false;
                    }

                    else if (tour_ == nullptr || roi_ == nullptr
                        || tour_->get_nom() != "\u2656" || roi_->get_nom() != "\u2654"){
                            cout << "tour et/ou roi manquant" << endl;
                            return false;
                        }
                    if (tour_->a_deja_bouge_fonction() || roi_->a_deja_bouge_fonction()){
                        cout << "tour et/ou roi ont deja bouge" << endl;
                        return false;
                    }
                    if(this->echiquier.case_attaquee(Square(7, 1), 0) || this->echiquier.case_attaquee(Square(7, 2), 0) || this->echiquier.case_attaquee(Square(7, 3), 0) || this->echiquier.case_attaquee(Square(7, 4), 0)){
                        cout << "une case du roque est attaquee ou le roi est en échec" << endl;
                        return false;
                    }
                    else{
                        return true;
                    }

            }

    }
    return false;        
}


void Jeu::effectuer_roque(bool petit_cote, unsigned char couleur, Echiquier &echiquier){
    switch (couleur){
        case 1 : //blanc
            if (petit_cote){
                Square case_depart_tour(0, 7);
                Square case_arrivee_tour(0, 5);
                Square case_depart_roi(0, 4);
                Square case_arrivee_roi(0, 6);

                Piece* tour = echiquier.getPiece(case_depart_tour);
                Piece* roi = echiquier.getPiece(case_depart_roi);
                this->echiquier.pose_piece(tour, case_arrivee_tour);
                this->echiquier.pose_piece(roi, case_arrivee_roi);
                this->echiquier.depart_piece(case_depart_tour);
                this->echiquier.depart_piece(case_depart_roi);

                tour->set_pos(case_arrivee_tour);
                roi->set_pos(case_arrivee_roi);

                this->tour_des_blancs = false;
                    
            }
            else {
                Square case_depart_tour(0, 0);
                Square case_arrivee_tour(0, 3);
                Square case_depart_roi(0, 4);
                Square case_arrivee_roi(0, 2);

                Piece* tour = echiquier.getPiece(case_depart_tour);
                Piece* roi = echiquier.getPiece(case_depart_roi);
                this->echiquier.pose_piece(tour, case_arrivee_tour);
                this->echiquier.pose_piece(roi, case_arrivee_roi);
                this->echiquier.depart_piece(case_depart_tour);
                this->echiquier.depart_piece(case_depart_roi);

                tour->set_pos(case_arrivee_tour);
                roi->set_pos(case_arrivee_roi);

                this->tour_des_blancs = false;

            }
            break;
        case 0 : //noir
            if (petit_cote){
                Square case_depart_tour(7, 7);
                Square case_arrivee_tour(7, 5);
                Square case_depart_roi(7, 4);
                Square case_arrivee_roi(7, 6);

                Piece* tour = echiquier.getPiece(case_depart_tour);
                Piece* roi = echiquier.getPiece(case_depart_roi);
                this->echiquier.pose_piece(tour, case_arrivee_tour);
                this->echiquier.pose_piece(roi, case_arrivee_roi);
                this->echiquier.depart_piece(case_depart_tour);
                this->echiquier.depart_piece(case_depart_roi);

                tour->set_pos(case_arrivee_tour);
                roi->set_pos(case_arrivee_roi);

                this->tour_des_blancs = true;
            }
            else {
                Square case_depart_tour(7, 0);
                Square case_arrivee_tour(7, 3);
                Square case_depart_roi(7, 4);
                Square case_arrivee_roi(7, 2);

                Piece* tour = echiquier.getPiece(case_depart_tour);
                Piece* roi = echiquier.getPiece(case_depart_roi);
                this->echiquier.pose_piece(tour, case_arrivee_tour);
                this->echiquier.pose_piece(roi, case_arrivee_roi);
                this->echiquier.depart_piece(case_depart_tour);
                this->echiquier.depart_piece(case_depart_roi);

                tour->set_pos(case_arrivee_tour);
                roi->set_pos(case_arrivee_roi);

                this->tour_des_blancs = true;

            }
    }
    return ;
}


void Jeu::deplace(std::string orig, std::string dest) {

    if (orig == "O-"){
        if (dest == "O"){
            if (roque_possible(true, this->tour_des_blancs, this->echiquier)){
                effectuer_roque(true, this->tour_des_blancs, this->echiquier);
                return;
            }
        }
        else if (dest == "O-"){
            if (roque_possible(false, this->tour_des_blancs, this->echiquier)){
                effectuer_roque(false, this->tour_des_blancs, this->echiquier);
                return;
            }
        }
    }

    else{

    Square origine(orig);
    Square destination(dest);

    if (!origine.existe() || !destination.existe()) {
        std::cout << "Coordonnées invalides" << std::endl;
        return;
    }

    Piece* piece = this->echiquier.getPiece(origine);

    Piece ***echiq = this->echiquier.get_echiquier();

    if (piece == nullptr) {
        std::cout << "Pas de pièce sur la case d'origine" << std::endl;
        return;
    }
    else if (piece->get_couleur() != this->tour_des_blancs) {
        std::cout << "Ce n'est pas votre tour" << std::endl;
        return;
    }

    else if ( prise_en_passant.est_prise_en_passant(origine, destination) ){
        cout << "prise en passant" << endl;
        piece->set_pos(destination);

        Piece *pion_pris_en_passant = prise_en_passant.get_pion_pouvant_etre_pris_en_passant(); 
        pion_pris_en_passant->affiche(); //test
        sauvegarde_piece_mangee = pion_pris_en_passant;

        this->echiquier.mort_piece(pion_pris_en_passant);
        this->echiquier.pose_piece(piece, destination);
        this->echiquier.depart_piece(origine);


    }


    else if (piece->deplacement(destination, (echiq))) {


        piece->set_pos(destination);


        if (this->echiquier.getPiece(destination) != nullptr) { //si piece sur case arrivée (forcément une pièce adverse, sinon déplacement retourne false)
                //on enlève la pièce adverse du jeu (on la supprime du tableau et des vecteurs
                //mais on la sauvegarde avant de la supprimer pour pouvoir la remettre si le coup est annulé
        
            this->sauvegarde_piece_mangee = this->echiquier.getPiece(destination);
            this->echiquier.mort_piece(this->echiquier.getPiece(destination));
        }

        this->echiquier.pose_piece(piece, destination);
        this->echiquier.depart_piece(origine);


    }
    else {
        std::cout << "Déplacement invalide" << std::endl;
        return;
    }

    if ( this->echiquier.detection_echec(this->tour_des_blancs ) ){
        std::cout << "Coup illégal car met votre roi en échec, rejouez" << std::endl;
        this->resultat_coup = COUP_ILLEGAL;
    } //détecte si le roi est en échec après le déplacement


    if (this->resultat_coup == COUP_ILLEGAL) {//le code suivant pourrait être remplacé par la fonction annuler_coup mais comme 1è utilisation, explicité

        this->echiquier.pose_piece(piece, origine);
        piece->set_pos(origine);
        this->echiquier.depart_piece(destination);

        Piece *piece_mangee = this->sauvegarde_piece_mangee;
        if (piece_mangee != nullptr) {
            piece_mangee->affiche();
            this->echiquier.resurrection_piece(piece_mangee); //ne fait que remettre la pièce dans le tableau et les vecteurs, la pièce est toujours présente dans la mémoire  
            //this->echiquier.pose_piece(piece_mangee, destination);
            piece_mangee->set_pos(destination);

            sauvegarde_piece_mangee = nullptr;
        }

        this->resultat_coup = COUP_NORMAL;

        
        return;
    }

    else{ //coup légal : on actualise ce qui doit l'être en sachant que le coup est légal et qu'il ne sera pas annulé

        if (piece->get_nom() == "\u265F" || piece->get_nom() == "\u2659") { //si c'est un pion
            Piece* &reference = piece;
            this->echiquier.promotion(reference, destination); //promeut si besoin
        }
        //à noter qu'il est important que la promotion soit effectuée avant la détection de l'échec car la pièce promue peut contrôler des cases supplémentaires
        //(ce qui m'a posé problème au début pour certains des tests de la partie 3)

        Piece *piece_mangee = sauvegarde_piece_mangee;
        if (piece_mangee != nullptr) {
            delete(piece_mangee); //supprime la pièce définitivement, était déjà "morte" mais pas encore libérée (était juste supprimée du tableau et des vecteurs)
            sauvegarde_piece_mangee = nullptr;
        }

        prise_en_passant.nettoyage(); // fait une fois que le coup est légal, pour ne rien perturber dans le déroulement du jeu si un coup doit être rejoué

        if (this->tour_des_blancs && piece->get_nom() == "\u265F" && origine.getRangee() == 1 && destination.getRangee() == 3) {//si un pion blanc bouge de deux cases
            this->prise_en_passant.remplissage_prise_en_passant(this->tour_des_blancs, origine.getColonne(), echiq);
            Piece* pion_pris_en_passant = prise_en_passant.get_pion_pouvant_etre_pris_en_passant();
            if (pion_pris_en_passant != nullptr) {
                pion_pris_en_passant->affiche();
            }
        }
        if (!this->tour_des_blancs && piece->get_nom() == "\u2659" && origine.getRangee() == 6 && destination.getRangee() == 4) {//si un pion noir bouge de deux cases
            this->prise_en_passant.remplissage_prise_en_passant(this->tour_des_blancs, origine.getColonne(), echiq);
            Piece* pion_pris_en_passant = prise_en_passant.get_pion_pouvant_etre_pris_en_passant();
            if (pion_pris_en_passant != nullptr) {
                pion_pris_en_passant->affiche();
            }
        }


        if (this->echiquier.detection_echec(!this->tour_des_blancs)){ //on regarde si le roi adverse est en échec après avoir promu (car l'échec peut être causé par la promotion)
            //créer un vecteur de pièces qui peuvent manger le roi adverse
            cout << "Echec" << endl;
            if (this->echiquier.detection_echec_et_mat(!this->tour_des_blancs)) {
                cout << "Echec et mat" << endl;
                this->stop = true;

                switch(this->tour_des_blancs){
                    case true:
                        cout << "Les blancs ont gagné" << endl;
                        this->resultat_partie = BLANC_GAGNE;
                        break;
                    case false:
                        cout << "Les noirs ont gagné" << endl;
                        this->resultat_partie = NOIR_GAGNE;
                        break;
                }

                return;
            }
        }

        else if (this->prise_en_passant.get_pion_pouvant_etre_pris_en_passant() == nullptr) {//si une prise en passant est possible, pas de pat
            if (this->echiquier.detection_pat(!this->tour_des_blancs)) { 
                cout << "Pat" << endl;
                this->stop = true;
                this->resultat_partie = VISER_LA_NULLE;
                return;
            }
        }




        string nom = piece->get_nom();
        if (nom == "\u265A" || nom == "\u2654"){
            Roi *roi = dynamic_cast<Roi*>(piece);
            roi->a_deja_bouge = true;   //cet attribut permet de vérifier que le roque est légal (voir fonction Jeu::roque_possible)
            cout << "Le roi a bougé" << endl;
        }

        if (nom == "\u265C" || nom == "\u2656"){
            Tour *tour = dynamic_cast<Tour*>(piece);
            tour->a_deja_bouge = true;  //idem
            cout << "La tour a bougé" << endl;
        }

        this->resultat_coup = COUP_NORMAL;
        this->tour_des_blancs = !this->tour_des_blancs;
    }

    }

}


void Jeu::affiche_fin() {
    cout << "Fin de la partie" << endl;
    cout << this->echiquier.canonical_position() << " " ;

    switch (this->resultat_partie) {
        case PAS_DEFINI:
            cout << "?-?" << endl;
            break;
        case BLANC_GAGNE:
            cout << "1-0";
            break;
        case NOIR_GAGNE:
            cout << "0-1" << endl;
            break;
        case VISER_LA_NULLE:
            cout << "1/2-1/2" << endl;
            break;
        default :
            cout << "Erreur" << endl;
            break;
    }



    return;
}


//--------------------------------------------------------------
int main() {
    Jeu monjeu;  // initialise le jeu
    string mouvement;
    monjeu.affiche();
    bool stop = monjeu.get_stop(); // stop = false
    do
    {
        cout << "Coup (eg. a1a8) ? ";
        cin >> mouvement;
        if (mouvement != "/quit") {
            // découper case origine et destination
            string orig = mouvement.substr(0, 2);
            string dest = mouvement.substr(2, 2);
            monjeu.deplace(orig, dest);
            monjeu.affiche();
        }
        else monjeu.set_stop(true);
        
        stop = monjeu.get_stop();
    } while (!stop);

    monjeu.affiche_fin(); 


}