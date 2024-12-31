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

        std::map<Booktype, std::vector<Livre*>> getDico() {
            return monDictionnaire;
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
            monDictionnaire[pmonlivre->getBT()] = monvecteur;
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
                std::cout<< "Exception Capturee";
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

        
        // methode pour quand un qdherent veut emprunter un livre
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


        // methode pour quand on prete de livre a une autre bibliotheque
        void PreterLivre(Livre* pmonLivre) {
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
                            monvecteur[i]->SetEtat(Prete);
                            break; // je sors de la boucle pour ne pas emprunter un autre meme livre 
                        }
                    }
                }
            } catch (const std::exception& e){
                std::cout<< "exception geree" << e.what() << "\n";
                //
            }
        }

        void Demander(Livre* pMonLivre, Bibliotheque& maBiblio) {
            try {
                
                if (!(maBiblio.ContientLivre(pMonLivre) && (pMonLivre->EstLibre()))){
                    // erreur pas ce livre dans cette bibliotheque ou alors deja emprunte
                    throw std::runtime_error("La Bibliotheque demandee ne possede pas ce livre ou il est deja emprunte");
                } else {
                    // alors la bibliotheque contient ce livre ET il est libre
                    // alors on ajoute une copie de ce livre, ou on precise son etat
                    // on utilise NEW afin que le pointeur soit valide
                    Livre* pCopie = new Livre(*pMonLivre);
                    this->AjouterLivre(pCopie);
                    std::cout<<"livre bien ajoute"<<"\n";

                    // puis on precise dans la biblio ou il a ete pris que il est emprunte
                    maBiblio.PreterLivre( pMonLivre);
                    

                    
            } 
        }catch (const std::exception& e) {
                std::cout<< "Exception Capturee";
            }
        }


        static Livre* ObtenirLivre( Livre* pLivre, Bibliotheque& mabiblio){
            std::vector<Livre*>& monvecteur = mabiblio.getDico()[pLivre->getBT()];
            try {
            for (int i=0; i<monvecteur.size(); i++) {
                if (pLivre->getCode() == monvecteur[i]->getCode()) {
                    // alors les deux livres sont EXAcTEMENT LES MEMES
                    return monvecteur[i];
                }
            }
            throw std::runtime_error("Livre exact non trouve");
             } catch ( const std::exception& e) {
                std::cout << "Erreur : " << e.what() << std::endl;
                return nullptr;
            } 
        }

        static void Modifier( Livre* pLivre, Bibliotheque& mabiblio, Etat monEtat){
            std::vector<Livre*>& monvecteur = mabiblio.getDico()[pLivre->getBT()];
            try {
            for (int i=0; i<monvecteur.size(); i++) {
                if (pLivre->getCode() == monvecteur[i]->getCode()) {
                    // alors les deux livres sont EXAcTEMENT LES MEMES
                    monvecteur[i]->SetEtat(monEtat);
                }
            }
            throw std::runtime_error("Livre exact non trouve");
             } catch ( const std::exception& e) {
                std::cout << "Erreur : " << e.what() << std::endl;
                
            } 
        }

        void Rendre(Livre* pLivre, Bibliotheque& maBibliotheque){
            try {
                if (this->ContientLivre(pLivre) && pLivre->getEtat() == Libre && (ObtenirLivre(pLivre, maBibliotheque) != nullptr) ) {
                    std::cout<<"etape 1 reussie";
                    // alors notre livre est disponible pour etre rendu, reste a verifier que c'est cette biblio 
                    // qui nous l'a prete 
                    if (ObtenirLivre(pLivre, maBibliotheque)->getEtat() == Prete){
                        // alors on est bien dans ce cas : la biblio nous a prete ce livre
                        // on lui rend
                        // ce livre precis de cette bibliotheque est desormais libre
                        Modifier(pLivre, maBibliotheque, Libre);
                    }


                    // finalement on supprime ce livre de chez nous, on ne l'a plus !
                    this->SupprimerLivre(pLivre);
                } else {
                    throw std::runtime_error(" on ne trouve pas exactement ce livre dans cette bibliotheque");
                }
            } catch ( const std::exception& e) {
                std::cout << "Erreur : " << e.what() << std::endl;
                
            } 

            
        }

};
#endif
