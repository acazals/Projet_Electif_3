#ifndef ROMAN_H
#define ROMAN_H
#include <iostream>
#include "livre.h"

class Roman : public Livre {
    private :
        std::string genre;

    public :
        Roman(int monCode, std::string monAuteur, std::string monEditeur, int monISBN, std::string monPublic, std::string monetat, std::string monGenre ) : Livre(monCode, monAuteur, monEditeur, monISBN, monPublic, monetat), genre(monGenre)
            {
            }

        std::string getGenre(){
            return genre;
        }

        void Afficher()
            {
            Livre::Afficher();
            std::cout<< "Genre" << getGenre() << "\n";
            
        }
};
#endif