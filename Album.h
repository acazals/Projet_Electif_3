#ifndef ALBUM_H
#define ALBUM_H
#include <iostream>
#include "livre.h"

class Album : public Livre {
    private :
        std::string illustrations;

    public : 

        Album(int monCode, std::string monAuteur, std::string monEditeur, int monISBN, std::string monPublic, Etat monetat, std::string mesillustrations ) : Livre(monCode, monAuteur, monEditeur, monISBN, monPublic, monetat), illustrations( mesillustrations)
            {
                Livre::myBT = BT_album;
            }

        Album (const Album& monAlbum) : Livre(monAlbum), illustrations(monAlbum.getIllustrations()) {
            this->setBT(BT_album);
        }

        std::string getIllustrations() const{
            return illustrations;
        }

        Booktype getBT(){
            return myBT;
        }

        void Afficher()
            {
            Livre::Afficher();
            std::cout<< "Illustrations" << getIllustrations() << "\n";
            
        }
        
};

#endif

