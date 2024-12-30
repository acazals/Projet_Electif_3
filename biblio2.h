#ifndef BIBLIOTHEQUE_H
#define BIBLIOTHEQUE_H
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <string>

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

        // valeur : pointeurs vers des livres
        std::map<Booktype, std::vector<Livre*>> monDictionnaire;
        
        int NbEmpruntsMax;

       


    public :

        void Bibliotheque ( int monCode, std::string monNom, std::string monAdresse, std::map<Booktype, std::vector<Livre*>> maListe, int monMax) {
            Code = monCode,
            nom = monNom;
            adresse = monAdresse;
            monDictionnaire = maListe;
            NbEmpruntsMax = monMax;
        }

        void AjouterLivre( Livre monLivre){
            
        }

        void Afficher( Booktype montype = BT_none){
            if (montype == BT_none){
                // on affiche tout
                for (const auto& paire: monDictionnaire){
                    const Booktype& maclef = paire.first;
                    const std::vector<Livre*>& monvecteur = paire.second;
                    std::cout<< "pour le type" << maclef << "\n";
                    for (Livre* livre : monvecteur){
                        livre->Afficher();
                    }
                }
            }

            if (montype == BT_rman) {

                // on affiche les livres par categorie 
                for (int i= 0; i< monDictionnaire[BT_rman].size(); i++){
                    monDictionnaire[BT_rman][i]->Afficher();
                }
                
            }
            if (montype == BT_pieceTheatre) {

                // on affiche les livres par categorie 
                for (int i= 0; i< monDictionnaire[BT_pieceTheatre].size(); i++){
                    monDictionnaire[BT_pieceTheatre][i]->Afficher();
                }
                
            }
            if (montype == BT_receuilPoesie) {

                // on affiche les livres par categorie 
                for (int i= 0; i< monDictionnaire[BT_receuilPoesie].size(); i++){
                    monDictionnaire[BT_receuilPoesie][i]->Afficher();
                }
                
            }if (montype == BT_bandeDessinee) {

                // on affiche les livres par categorie 
                for (int i= 0; i< monDictionnaire[BT_receuilPoesie].size(); i++){
                    monDictionnaire[BT_receuilPoesie][i]->Afficher();
                }
                
            }if (montype == BT_album) {

                // on affiche les livres par categorie 
                for (int i= 0; i< monDictionnaire[BT_album].size(); i++){
                    monDictionnaire[BT_album][i]->Afficher();
                }
                
            }
            
            
        }

};
#endif
