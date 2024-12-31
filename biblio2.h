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

class Bibliotheque {
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

        Bibliotheque ( int monCode, std::string monNom, std::string monAdresse, std::map<Booktype, std::vector<Livre*>> maListe, int monMax) {
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

        bool ContientLivre(Livre* MonLivre)  {
            // on recupere la vector associe au type
            // si la bibliotheque ne possede pas de livres de ce type alors ca va creer un vecteur vide
            std::vector<Livre*>& monvecteur = monDictionnaire[MonLivre->getBT()];
            for (int i=0; i<monvecteur.size(); i++) {
                if (MonLivre == monvecteur[i]) {
                    // operateur == base sur l'ISBN
                    return true;
                }
            }
            return false;
            // si livre pas trouve alors false
        }

        void SupprimerLivre(Livre* pmonlivre){
            // on fait  une reference du vecteur pour avoir l'objet monvecteur
            // monvecteur plus facile a utiliser que monDIctionnaire...
            std::vector<Livre*>& monvecteur = monDictionnaire[pmonlivre->getBT()];
            for (int i=0; i< monvecteur.size(); i++ ) {
                if (*monvecteur[i] == *pmonlivre){
                    // on prend le vecteur et onsuprime l'element correspondant
                    // pour cela on utilise un iterateur
                    monvecteur.erase( monvecteur.begin() +i);                    
                }
            }
            // puis on remet l'objet final ou tout les livres correspondants ont ete supprimes
            //monDictionnaire[pmonlivre->getBT()] = monvecteur;
        }

        void Afficher( Booktype montype = BT_none){
            if (montype == BT_none){
                // on affiche tout
                for (const auto& paire: monDictionnaire){
                    std::cout<<"\n";
                    const Booktype& maclef = paire.first;
                    const std::vector<Livre*>& monvecteur = paire.second;
                    std::cout<< "pour le type " << booktypeToString(maclef) << "\n";
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

        

        void EmprunterLivre(Livre* pmonLivre) {
            try {
                if (!(this->ContientLivre(pmonLivre) && (pmonLivre->EstLibre()))) {
                    throw std::runtime_error("Le livre n'est pas disponible a l'emprunt dans la bibliotheque");
                } else {
                    // livre present et libre dans la bibliotheque
                    // on prend le vecteur qui correspond
                    std::vector<Livre*>& monvecteur = monDictionnaire[pmonLivre->getBT()];
                    for (int i=0; i<monvecteur.size(); i++){
                        if ((monvecteur[i] == pmonLivre) && monvecteur[i]->EstLibre()){
                            // alors on a trouve le livre qui correspond : bon ISBN et bien libre
                            monvecteur[i]->SetEtat(Emprunte);
                            break; // je sors de la boucle pour ne pas emprunter un autre meme livre 
                        }
                    }
                }
            } catch (const std::exception& e){
                std::cout<< "exception geree" << e.what() << "\n";
                //
            }
        }

        void Demander(Livre* pMonLivre, Bibliotheque maBiblio) {
            try {
                
                if (!(maBiblio.ContientLivre(pMonLivre) && (pMonLivre->EstLibre()))){
                    // erreur pas ce livre dans cette bibliotheque ou alors deja emprunte
                    throw std::runtime_error("La Bibliotheque demandee ne possede pas ce livre ou il est deja emprunte");
                } else {
                    // alors la bibliotheque contient ce livre ET il est libre
                    // alors on ajoute une copie de ce livre, ou on precise son etat
                    Livre Copie = *pMonLivre; 
                    Copie.SetEtat(Libre); // le livre peut etre emprunte dans la nouvelle bibliotheque 
                    // on cree un pointeur de la copie afin de la rajouter a ma biblio
                    Livre* pCopie = &Copie;
                    this->AjouterLivre(pCopie);

                    // puis on precise dans la biblio ou il a ete pris que il est emprunte
                    maBiblio.EmprunterLivre( pMonLivre);
                    

                    
            } 
        }catch (const std::exception& e) {
                std::cout<< "Exception Capturee";
            }
        }

};
#endif
