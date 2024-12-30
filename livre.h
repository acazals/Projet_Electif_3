#ifndef LIVRE_H
#define LIVRE_H
#include <iostream>

// class Booktype de type enum : permet 
enum Booktype {BT_none, BT_rman, BT_bandeDessinee, BT_album, BT_receuilPoesie, BT_pieceTheatre};

class Livre {

    private :
        int code;
        std::string auteur;
        std::string editeur;
        int ISBN;
        std::string Public;
        std::string etat;
        
    protected :
        Booktype myBT;

    public : 

        Livre(int moncode, std::string monauteur, std::string monediteur, int monISBN, std::string monpublic, std::string monetat){
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
            std::cout<< " etat : " << getEtat() << "\n";
            std::cout<< " etat : " << getEtat() << "\n";
        };

        int getCode() const{
            return code;
        }

        std::string getEtat() const{
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

        void Emprunter(){
            if (etat == "libre") {
                etat = "emprunte";
            }
        }

        void Preter() {
            if (etat == "libre") {
                etat = "prete";
            }
        }

        void Rendre() {
            if (etat != "libre") {
                etat = "libre";
            }
        }




};

#endif
