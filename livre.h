#ifndef LIVRE_H
#define LIVRE_H
#include <iostream>
class Bibliotheque;

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

enum Etat {Libre, Emprunte};

std::string etatToString(Etat etat) {
    switch (etat) {
        case Libre: return "Libre";
        case Emprunte: return "Emprunte";
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
        bool preteAutreBiblio;
        Bibliotheque* Proprietaire;
        Bibliotheque* Emprunteuse;
        
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
            Proprietaire = nullptr;
            Emprunteuse = nullptr;
            bool preteAutreBiblio = false;


        }

        Livre(const Livre& monLivre){
            code = monLivre.getCode();
            auteur = monLivre.getAuteur();
            editeur = monLivre.getEditeur();
            ISBN = monLivre.getISBN();
            Public = monLivre.getPublic();
            etat = monLivre.getEtat();
            myBT = monLivre.getBT();
            Proprietaire = monLivre.getProprio();
            Emprunteuse = monLivre.getEmprunteuse();
            preteAutreBiblio = monLivre.getEstPreteAutreBiblio();



        } // C++, le constructeur de recopie doit recevoir un paramètre de type référence constante à l'objet de la classe

        Booktype getBT() const{
            return myBT;
        }

        void setProprietaire(Bibliotheque* maBiblio){
            this->Proprietaire = maBiblio;
        }

        void setReceveuse(Bibliotheque* Emprunteuse) {
            this->Emprunteuse = Emprunteuse;
           
        }

        void setPreteAutreBiblio(bool temp) {
            this->preteAutreBiblio = temp;
            
        }


        bool getEstPreteAutreBiblio() const {
            return preteAutreBiblio;
        }

        
        Bibliotheque* getProprio() const{
            return this->Proprietaire;
        }

        Bibliotheque* getEmprunteuse() const {
            return this->Emprunteuse;
        }

        void setBT(Booktype monBT){
            myBT = monBT;
        }

        virtual void Afficher() {
            std::cout<< " code : " << getCode() << "\n";
            std::cout<< " auteur : " << getAuteur() << "\n";
            std::cout<< " editeur : " << getEditeur() << "\n";
            std::cout<< " ISBN : " << getISBN() << "\n";
            std::cout<< " Public : " << getPublic() << "\n";
            std::cout<< " etat : " << etatToString(getEtat()) << "\n";
            std::cout<< "BT: " << booktypeToString(myBT) << "\n";
            std::cout<< "Est pretee autre biblio " << this->getEstPreteAutreBiblio() <<"\n";
            std::cout<< "Proprio "<< this->getProprio() << "\n";
            std::cout<< "Emprunteuse " << this->getEmprunteuse()<< "\n";
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

        std::string getPublic() const {
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
