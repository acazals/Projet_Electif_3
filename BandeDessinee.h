#ifndef BANDEDESSINEE_H
#define BANDEDESSINEE_H
#include <iostream>
#include "livre.h"

class BandeDessinee : public Livre {
    private :
        std::string Dessinateur;

    public : 

        BandeDessinee(int monCode, std::string monAuteur, std::string monEditeur, int monISBN, std::string monPublic, std::string monetat, std::string mondessinateur ) : Livre(monCode, monAuteur, monEditeur, monISBN, monPublic, monetat), Dessinateur( mondessinateur)
            {
            }

        std::string GetDessinateur(){
            return Dessinateur;
        }



        void Afficher()
            {
            Livre::Afficher();
            std::cout<< "Dessinateur" << GetDessinateur() << "\n";
            
        }
        
};

#endif
