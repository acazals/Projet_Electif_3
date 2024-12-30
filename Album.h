#ifndef ALBUM_H
#define ALBUM_H
#include <iostream>
#include "livre.h"

class Album : public Livre {
    private :
        std::string illustrations;

    public : 

        Album(int monCode, std::string monAuteur, std::string monEditeur, int monISBN, std::string monPublic, std::string monetat, std::string mesillustrations ) : Livre(monCode, monAuteur, monEditeur, monISBN, monPublic, monetat), illustrations( mesillustrations)
            {
            }

        std::string getIllustrations(){
            return illustrations;
        }

        void Afficher()
            {
            Livre::Afficher();
            std::cout<< "Illustrations" << getIllustrations() << "\n";
            
        }
        
};

#endif

