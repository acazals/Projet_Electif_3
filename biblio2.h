#ifndef BIBLIOTHEQUE_H
#define BIBLIOTHEQUE_H
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

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

        void AjouterLivre( Livre* pmonLivre){
            // on recupere le vecteur correspondant
            // on y ajoute un pointeur vers le livre
            monDictionnaire[pmonLivre->getBT()].push_back(pmonLivre);
        }

        void SupprimerLivre(Livre* pmonlivre){
            // on fait  une copie du vecteur pour avoir l'objet monvecteur
            std::vector<Livre*> monvecteur = monDictionnaire[pmonlivre->getBT()];
            for (int i=0; i< monvecteur.size(); i++ ) {
                if (*monvecteur[i] == *pmonlivre){
                    // on prend le vecteur et onsuprime l'element correspondant
                    // pour cela on utilise un iterateur
                    monvecteur.erase( monvecteur.begin() +i);                    
                }
            }
            // puis on remet l'objet final ou tout les livres correspondants ont ete supprimes
            monDictionnaire[pmonlivre->getBT()] = monvecteur;
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

            else {

                // on affiche les livres par categorie 
                for (int i= 0; i< monDictionnaire[montype].size(); i++){
                    monDictionnaire[montype][i]->Afficher();
                }
                
            }
            
            
            
        }

};
#endif
