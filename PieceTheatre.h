#ifndef PIECETHEATRE_H
#define PIECETHEATRE_H
#include <iostream>
#include "livre.h"

class PieceTheatre : public Livre {
    private :
        int siecle;

    public :

        PieceTheatre(int monCode, std::string monAuteur, std::string monEditeur, int monISBN, std::string monPublic, std::string monetat, int monsiecle ) : Livre(monCode, monAuteur, monEditeur, monISBN, monPublic, monetat), siecle(monsiecle)
            {
            }

        int getSiecle(){
            return siecle;
        }

        void Afficher()
            {
            Livre::Afficher();
            std::cout<< "Siecle" << getSiecle() << "\n";
            
        }

};

#endif