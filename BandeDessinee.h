#ifndef BANDEDESSINEE_H
#define BANDEDESSINEE_H
#include <iostream>
#include "livre.h"

class BandeDessinee : public Livre {
    private :
        std::string Dessinateur;

    public : 

        BandeDessinee(int monCode, std::string monAuteur, std::string monEditeur, int monISBN, std::string monPublic, Etat monetat, std::string mondessinateur ) : Livre(monCode, monAuteur, monEditeur, monISBN, monPublic, monetat), Dessinateur( mondessinateur)
            {
                Livre::myBT = BT_bandeDessinee;
            }

        BandeDessinee(const BandeDessinee& maBD) : Livre(maBD), Dessinateur(maBD.GetDessinateur()){
            this->setBT(BT_bandeDessinee);
        }

        std::string GetDessinateur() const{
            return Dessinateur;
        }

        Booktype getBT(){
            return myBT;
        }


        void Afficher()
            {
            Livre::Afficher();
            std::cout<< "Dessinateur" << GetDessinateur() << "\n";
            
        }
        
};

#endif

