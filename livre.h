#ifndef LIVRE_H
#define LIVRE_H
#include <iostream>

// class Booktype de type enum : permet 
enum Booktype {BT_none, BT_rman, BT_bandeDessinee, BT_album, BT_receuilPoesie, BT_pieceTheatre};

std::string booktypeToString(Booktype bt) {
    switch (bt) {
        case BT_none: return "BT_none";
        case BT_rman: return "BT : Roman";
        case BT_bandeDessinee: return "BT : BandeDessinee";
        case BT_album: return "BT_album";
        case BT_receuilPoesie: return "BT ReceuilPoesie";
        case BT_pieceTheatre: return "BT : PieceTheatre";
        default: return "Unknown";
    }
}

enum Etat {Libre, Prete, Emprunte, EmprunteAutreBiblio, PreteAutreBiblio};

std::string etatToString(Etat etat) {
    switch (etat) {
        case Libre: return "Libre";
        case Prete: return "Prete";
        case Emprunte: return "Emprunte";
        case EmprunteAutreBiblio: return "Emprunte par une autre Biblio";
        case PreteAutreBiblio: return "Prete a une autre Biblio";
        default: return "Unknown";
    }
}

class Livre {

    private :
        int code;
        std::string auteur;
        std::string editeur;
        int ISBN;
        std::string Public;
        Etat etat;
        
    protected :
        Booktype myBT;

    public : 

        Livre(int moncode, std::string monauteur, std::string monediteur, int monISBN, std::string monpublic, Etat monetat){
            code = moncode;
            auteur = monauteur;
            editeur = monediteur;
            ISBN = monISBN;
            Public = monpublic;
            etat = monetat;
            myBT= BT_none;

        }

        Booktype getBT() const{
            return myBT;
        }

        virtual void Afficher() {
            std::cout<< " code : " << getCode() << "\n";
            std::cout<< " auteur : " << getAuteur() << "\n";
            std::cout<< " editeur : " << getEditeur() << "\n";
            std::cout<< " ISBN : " << getISBN() << "\n";
            std::cout<< " Public : " << getPublic() << "\n";
            std::cout<< " etat : " << etatToString(getEtat()) << "\n";
            std::cout<< "BT: " << booktypeToString(myBT) << "\n";
        };

        int getCode() const{
            return code;
        }

        Etat getEtat() const{
            return etat; 
        }

        int getISBN() const{
            return ISBN;
        }

        std::string getAuteur() const{
            return auteur;
        }

        std::string getEditeur() const{
            return editeur;
        }

        std::string getPublic() {
            return Public;
        }

        void SetEtat (Etat monetat) {
            etat = monetat;
        }

        void Emprunter(){
            if (etat == Libre) {
                etat = Emprunte;
            }
        }

        void EmpruntAutreBiblio() {
            if (etat == Libre) {
                etat = EmprunteAutreBiblio;
            }
        }

        void RendreAutreBiblio(){
            if (etat == EmprunteAutreBiblio){
                etat = Libre;
            }
        }

        void Preter() {
            if (etat == Libre) {
                etat = Emprunte;
            }
        }

        void Rendre() {
            if (etat != Libre) {
                etat = Libre;
            }
        }

        bool EstLibre() {
            if (etat!= Libre) {
                return false;
            }
            return true;
        }

        bool Isequal(Livre& autreLivre) {
           
            if (( this->ISBN == autreLivre.getISBN()))
            {   return true;}
            return false;
        }

        bool operator== (const Livre& other) const {
            return (this->ISBN == other.getISBN());
        }

        bool operator< (const Livre& other) const {
            return this->ISBN < other.getISBN();
        }




};

#endif
