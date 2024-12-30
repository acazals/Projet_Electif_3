#ifndef BIBLIOTHEQUE_H
#define BIBLIOTHEQUE_H
#include <iostream>
#include <string>
#include <list>
#include <vector>

#include "Album.h"
#include "BandeDessinee.h"
#include "Roman.h"
#include "ReceuilPoesie.h"
#include "PieceTheatre.h"

class Bibiotheque {
    private :
        int Code;
        std::string nom;
        std::string adresse;
        // dico avec des pointeurs comme valeurs a la place des instances elles meme
        // on utilise comme clef 
        
        int NbEmpruntsMax;

       


    public :

        void Bibliotheque ( int monCode, std::string monNom, std::string monAdresse, std::vector<Livre> maListe, int monMax) {
            Code = monCode,
            nom = monNom;
            adresse = monAdresse;
            ListeLivre = maListe;
            NbEmpruntsMax = monMax;
        }

        void AjouterLivre( Livre monLivre){
            
        }

        void Afficher(bool var){
            if (var){
                // on affiche tous les livres
                for (int i=0; i<ListeLivre.size(); i++){
                    ListeLivre[i].Afficher();
                }

            } else {
                // on affiche les livres par categorie 
                
            }
        }

};
#endif
