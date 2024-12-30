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
        std::vector<Livre> ListeLivre;

        std::vector<Livre> ListeAlbum;
        std::vector<Livre> ListePoesie;
        std::vector<Livre> ListeRoman;
        std::vector<Livre> ListeBD;
        std::vector<Livre> ListePiece;
        
        int NbEmpruntsMax;

        void organisation() {
            for (int i=0; i<ListeLivre.size(); i++) {
                if (ListeLivre[i].getBT() == BT_album){
                    ListeAlbum.push_back(ListeLivre[i]);

                }
                if (ListeLivre[i].getBT() == BT_bandeDessinee){
                    ListeBD.push_back(ListeLivre[i]);
                }
                if (ListeLivre[i].getBT() == BT_pieceTheatre){
                    ListePiece.push_back(ListeLivre[i]);
                }
                if (ListeLivre[i].getBT() == BT_receuilPoesie){
                    ListePoesie.push_back(ListeLivre[i]);
                }
                if (ListeLivre[i].getBT() == BT_rman){
                    ListeRoman.push_back(ListeLivre[i]);
                }
            } 
        }


    public :

        void Bibliotheque ( int monCode, std::string monNom, std::string monAdresse, std::vector<Livre> maListe, int monMax) {
            Code = monCode,
            nom = monNom;
            adresse = monAdresse;
            ListeLivre = maListe;
            NbEmpruntsMax = monMax;
        }

        void AjouterLivre( Livre monLivre){
            ListeLivre.push_back(monLivre);
                if (monLivre.getBT() == BT_album){
                    ListeAlbum.push_back(monLivre);

                }
                if (monLivre.getBT() == BT_bandeDessinee){
                    ListeBD.push_back(monLivre);
                }
                if (monLivre.getBT() == BT_pieceTheatre){
                    ListePiece.push_back(monLivre);
                }
                if (monLivre.getBT() == BT_receuilPoesie){
                    ListePoesie.push_back(monLivre);
                }
                if (monLivre.getBT() == BT_rman){
                    ListeRoman.push_back(monLivre);
                }
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
