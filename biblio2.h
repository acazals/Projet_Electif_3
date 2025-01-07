#ifndef BIBLIOTHEQUE_H
#define BIBLIOTHEQUE_H
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

#include "livre.h"
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

        int getMax(){
            return NbEmpruntsMax;
        }

        std::map<Booktype, std::vector<Livre*>> getDico() {
            return monDictionnaire;
        }

        std::string getNom() {
            return this->nom;
        }

        void AjouterLivre( Livre* pmonLivre){
            // on recupere le vecteur correspondant
            // on y ajoute un pointeur vers le livre
            try {
                if (pmonLivre == nullptr){
                throw std::runtime_error("livre = pointeur nul");
            }
            // on ajoute le livre au vecteur et on definit son proprietaire
            monDictionnaire[pmonLivre->getBT()].push_back(pmonLivre);
            pmonLivre->setProprietaire(this); }
            catch (const std::exception& e) {
                std::cout<< "Exception Capturee : on ne peut pas ajouter un nullptr";
            }
            
        }

        void AjouterLivreDePret( Livre* pmonLivre){ // cas ou on ajoute un livre qui nous a ete prete !!
            // on recupere le vecteur correspondant
            // on y ajoute un pointeur vers le livre
            try {
                if (pmonLivre == nullptr){
                throw std::runtime_error("livre = pointeur nul");
            }
            // on ajoute le livre au vecteur et on definit son emprunteur
            pmonLivre->setReceveuse(this);
            pmonLivre->setPreteAutreBiblio(true);
            monDictionnaire[pmonLivre->getBT()].push_back(pmonLivre);
            
            }
            catch (const std::exception& e) {
                std::cout<< "Exception Capturee : on ne peut pas ajouter un nullptr";
            }
            
        }

        // methode qui verifie aue la biblio contient EXACTEMENT cet exemplaire du livre
        bool ContientLivre(Livre* MonLivre)  {
            // on recupere la vector associe au type
            // si la bibliotheque ne possede pas de livres de ce type alors ca va creer un vecteur vide

            try {
                if (MonLivre == nullptr) {
                    throw std::runtime_error("pointeur nul");
                }

            std::vector<Livre*>& monvecteur = monDictionnaire[MonLivre->getBT()];
            for (int i=0; i<monvecteur.size(); i++) {
                    // operateur == sur des pointeurs : compare l'adresse memoire
                    // renvoie true uniquement si c'est le mm objet 
                if ( (monvecteur[i] != nullptr) && MonLivre == monvecteur[i]) {

                    return true;
                }
            }
            return false;
             } 
            catch (const std::exception& e) {
                std::cout<< "Exception Capturee" << e.what() << "\n";
                return false;
            }
            // si livre pas trouve alors false
        }

        bool ContientExemplaire(Livre* MonLivre)  {
            // on recupere la vector associe au type
            // si la bibliotheque ne possede pas de livres de ce type alors ca va creer un vecteur vide

            try {
                if (MonLivre == nullptr) {
                    throw std::runtime_error("pointeur nul");
                }

            std::vector<Livre*>& monvecteur = monDictionnaire[MonLivre->getBT()];
            for (int i=0; i<monvecteur.size(); i++) {
                    // operateur == sur des instances de livres : compare les ISBN 
                if ( (monvecteur[i] != nullptr) && *MonLivre == *monvecteur[i]) {

                    return true;
                }
            }
            return false;
             } 
            catch (const std::exception& e) {
                std::cout<< "Exception Capturee" << e.what() << "\n";
                return false;
            }
            // si livre pas trouve alors false
        }


        // methode pour emprunter un autre exemplaire d'un livre
        Livre* AutreExemplaireLibre(Livre* pMonLivre) {
            try {
                    if (pMonLivre == nullptr) {
                        throw std::runtime_error("pointeur nul");
                    }

                std::vector<Livre*>& monvecteur = monDictionnaire[pMonLivre->getBT()];
                for (int i=0; i<monvecteur.size(); i++) {
                        // operateur == sur des objets Livre : utilise la redefinition d'operateur ==
                        
                    if ( (monvecteur[i] != nullptr) && *pMonLivre == *monvecteur[i]) {
                        if (monvecteur[i]->EstLibre()){
                            return monvecteur[i];
                        }
                        
                    }
                }

                throw std::runtime_error(" Pas de meme exemplaire de ce livre ou alors deja emprunte aussi;");
                } 
                catch (const std::exception& e) {
                    std::cout<< "Exception Capturee" << e.what() << "\n";
                    return nullptr;
                }
                // pas de mm exemplaire de libre
            }


        void SupprimerLivre(Livre* pmonlivre){
            // on fait  une reference du vecteur pour avoir l'objet monvecteur
            // monvecteur plus facile a utiliser que monDIctionnaire...

            try {
                if (pmonlivre == nullptr){ throw std::runtime_error("pointeur nul");}
            std::vector<Livre*>& monvecteur = monDictionnaire[pmonlivre->getBT()];
            for (int i=0; i< monvecteur.size(); i++ ) {
                if ( (monvecteur[i] != nullptr) && *monvecteur[i] == *pmonlivre){
                    // on prend le vecteur et onsuprime l'element correspondant
                    // pour cela on utilise un iterateur
                    monvecteur.erase( monvecteur.begin() +i);                    
                }
            }
             }
            catch (const std::exception& e) {
                std::cout<< "Exception Capturee" << e.what() << "\n";
            }
        }

        void SupprimerLivre2(Livre* pmonLivre) {
            try {
                if (this->ContientLivre(pmonLivre)){
                    // la bibliotheque contient bien ce livre alors on le supprime
                    std::vector<Livre*>& monvecteur =  monDictionnaire[pmonLivre->getBT()];
                    // Chercher l'élément à supprimer (pmonLivre est déjà un Livre* ici)
                    auto it = std::find(monvecteur.begin(), monvecteur.end(), pmonLivre);  // Trouver l'élément

                    if (it != monvecteur.end()) {
                        // Si l'élément est trouvé, supprimer l'élément du vecteur
                        delete *it;  // Libérer la mémoire de l'objet pointé par l'itérateur
                        monvecteur.erase(it);  // Supprimer l'élément du vecteur
                    } 
                   
                } else {
                    throw std::runtime_error("Livre non existant");
                }
            }catch (const std::exception& e) {
                std::cout<< "Exception Capturee" << e.what() << "\n";
            }
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

        


        
        void Demander(Livre* pMonLivre, Bibliotheque& maBiblio) {
            try {
                if (pMonLivre == nullptr) {
                    throw std::runtime_error("livre passe en argument = pointeur nul");
                }
                
                if (!(maBiblio.ContientLivre(pMonLivre) && (pMonLivre->EstLibre()))) {
                    throw std::runtime_error("La Bibliotheque demandee ne possede pas ce livre ou il est deja emprunte");
                }

                if (pMonLivre->getEstPreteAutreBiblio() == true) {
                    throw std::runtime_error("deja prete autre part");
                }

                // Debug : affichage avant modification
                std::cout << "Avant modification : \n";
                std::cout << "Est pretee autre biblio : " << pMonLivre->getEstPreteAutreBiblio() << "\n";
                std::cout << "Receveuse : " << pMonLivre->getEmprunteuse() << "\n";

                // Modification
                pMonLivre->setPreteAutreBiblio(true);
                pMonLivre->setReceveuse(this);  
                this->AjouterLivreDePret(pMonLivre);

                // Debug : affichage après modification
                std::cout << "Apres modification : \n";
                std::cout << "Est pretee autre biblio : " << pMonLivre->getEstPreteAutreBiblio() << "\n";
                std::cout << "Receveuse  test 1 : " << pMonLivre->getEmprunteuse() << "\n";

            } catch (const std::exception& e) {
                std::cout << "Exception Capturee: " << e.what() << "\n";
            }
        }


        void Rendre(Livre* pMonLivre) {
            try {
                if (this->ContientLivre(pMonLivre) == false ) {
                    throw std::runtime_error("Livre pas dans cette bibliotheque! \n");
                }
                if (pMonLivre->getEstPreteAutreBiblio() == false) {
                    throw std::runtime_error("Livre qui n'a pas ete emprunte par une autre biblio! \n");
                } if (pMonLivre->EstLibre() == true) {
                    throw std::runtime_error("Livre actuellement emprunte par un adherent !  \n");
                } else {
                    pMonLivre->setPreteAutreBiblio(false); // livre plus prete
                    pMonLivre->setReceveuse(nullptr);
                }
            }
            catch( const std::exception& e) {
                std::cout<< "Exception Capturee \n" << e.what() << "\n";
            }
        } 



};
#endif
