#ifndef RECEUILPOESIE_H
#define RECEUILPOESIE_H
#include "livre.h"

class ReceuilPoesie : public Livre {
     private :
        std::string Indicateur;

    public : 

        ReceuilPoesie(int monCode, std::string monAuteur, std::string monEditeur, int monISBN, std::string monPublic, Etat monetat, std::string monIndicateur ) : Livre(monCode, monAuteur, monEditeur, monISBN, monPublic, monetat), Indicateur(monIndicateur)
            {
                myBT = BT_receuilPoesie;
            }
        
        ReceuilPoesie( const ReceuilPoesie& monLIvre) : Livre(monLIvre), Indicateur(monLIvre.getIndicateur()){
            this->setBT(BT_receuilPoesie);
        }

        Booktype getBT() const{
            return myBT;
        }

        std::string getIndicateur() const{
            return Indicateur;
        }

        void Afficher()
            {
            Livre::Afficher();
            std::cout<< "Indicateur" << getIndicateur() << "\n";
            
        }
};
#endif