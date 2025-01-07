#ifndef ADHERENT_H
#define ADHERENT_H
#include <iostream>
#include "livre.h"
#include "biblio2.h"


class Adherent {
    private :
        std::string nom;
        std::string prenom;
        int NumeroAdherent;
        Bibliotheque* maBiblio;
        std::vector<Livre*> LivresEmpruntes;
        
    public : 

        Adherent(std::string nom, std::string prenom, int numeroAdherent, Bibliotheque* maBiblio)
        : nom(nom), prenom(prenom), NumeroAdherent(numeroAdherent), maBiblio(maBiblio) {}

         

        Adherent(const Adherent& other) {
            this->nom = other.getNom();
            this->prenom = other.getPrenom();
            this->NumeroAdherent = other.getNumeroAdherent();
            this->maBiblio = other.getMaBiblio();
            this->LivresEmpruntes = other.getCopieLivre();
        }

        // Getters
    std::string getNom() const {
        return nom;
    }

    std::string getPrenom() const {
        return prenom;
    }

    int getNumeroAdherent() const {
        return NumeroAdherent;
    }

    Bibliotheque* getMaBiblio() const {
        return maBiblio;
    }

    std::vector<Livre*> getCopieLivre() const {
        return LivresEmpruntes;
    }

    std::vector<Livre*>& getLivresEmpruntes() {
        return LivresEmpruntes;
    }

    // Setters
    void setNom(const std::string& nouveauNom) {
        nom = nouveauNom;
    }

    void setPrenom(const std::string& nouveauPrenom) {
        prenom = nouveauPrenom;
    }

    void setNumeroAdherent(int nouveauNumero) {
        if (nouveauNumero > 0) {
            NumeroAdherent = nouveauNumero;
        } else {
            std::cout << "Numéro d'adhérent invalide.\n";
        }
    }

    void setMaBiblio(Bibliotheque* nouvelleBiblio) {
        maBiblio = nouvelleBiblio;
    }

    void setLivresEmpruntes(const std::vector<Livre*>& nouveauxLivres) {
        LivresEmpruntes = nouveauxLivres;
    }

    int NbEmprunts(){
        return LivresEmpruntes.size();
    }

    void afficher() const {
        std::cout << "Nom: " << nom << "\n";
        std::cout << "Prénom: " << prenom << "\n";
        std::cout << "Numéro d'adhérent: " << NumeroAdherent << "\n";
        std::cout << "Bibliothèque: " << maBiblio->getNom() << "\n"; // Affiche le nom de la bibliothèque associée

        std::cout << "Livres empruntés:\n";
        if (LivresEmpruntes.empty()) {
            std::cout << "Aucun livre emprunté.\n";
        } else {
            for (auto livre : LivresEmpruntes) {
                livre->Afficher();
            }
        }
}

    


    // prendre en compte que une bibliotheque peut avoir plusieurs exemplaires d'un livre
    void Emprunter (Livre* monLivre) {
        try {
            // gestion des erreurs 
            if (monLivre == nullptr) {
                throw std::runtime_error("Livre = nullptr");
                
            }
            // livre= nullptr
            else if (this->NbEmprunts() >= this->getMaBiblio()->getMax()){
                throw std::runtime_error("TROP DE LIVRES DEJA EMPRUNTES");
                
            } else if (this->AEmprunteOuCopie(monLivre) == true) {
                throw std::runtime_error("l'adherent a deja emprunte ce livre ou une copie");
            }
             // trop de livres deja empruntes
            else if (this->getMaBiblio()->ContientExemplaire(monLivre) == false){
                throw std::runtime_error("Pas d'exemplaires de ce livre dans la biblio");
                
            } // probleme : pas  d'exemplairesdans la biblio
            else if (monLivre->EstLibre() == false && maBiblio->AutreExemplaireLibre(monLivre) == nullptr) {
                // le livre precis est deja emprunte 
                // et pas de meme exemplaire de libre
                throw std::runtime_error("erreur : livre deja emprunte et pas de meme exemplaire de disponible");
                // livre qui a deja ete emprunte
            } else if (monLivre->EstLibre() == false && maBiblio->AutreExemplaireLibre(monLivre) != nullptr) {
                // alors notre livre precis est deja emprunte par contre il y a un autre exemplaire de libre
                // verifier que le livre est libre mais bien dans notre bibliotheque 
                Livre* autreexemplaire = maBiblio->AutreExemplaireLibre(monLivre);

                // on verifie que si le livre est pas emprunte il est bien a nous
                // et que si il est emprunte il est bien prete chez nous
                if ( (autreexemplaire->getEstPreteAutreBiblio() == false &&autreexemplaire->getProprio() == this->getMaBiblio() ) || ( autreexemplaire->getEstPreteAutreBiblio() == true && autreexemplaire->getEmprunteuse() == this->getMaBiblio()) ){
                    // alors on est dans le cas ou le livre est a nous OU ALORS nous est prete
                    // d'abord on ajoute le livre a notre liste de livres empruntes
                    this->LivresEmpruntes.push_back(maBiblio->AutreExemplaireLibre(autreexemplaire));
                    maBiblio->AutreExemplaireLibre(autreexemplaire)->SetEtat(Emprunte);
                    std::cout<<"le livre exact demande n'etait pas dispo mais l'adherent a pu emprunter un autre exemplaire \n";
                    // ensuite on precise que il a ete emprunte
                } else {
                    throw std::runtime_error("");
                }
                

            }
            
             // a ce stade la biblio contient le livre et il est libre
            // reste a verifier que il n'est pas prete autre part

            else if ((monLivre->getEstPreteAutreBiblio() == true && monLivre->getEmprunteuse() == this->getMaBiblio()) || (monLivre->getEstPreteAutreBiblio() == false && monLivre->getProprio() == this->getMaBiblio()) ){
                // soit c'est un livre  qui nous a ete prete
                // soit  livre non prete ET on est proprio donc on peut le preter
                this->LivresEmpruntes.push_back(monLivre); // on ajoute le livre dans nos livres empruntes
                monLivre->SetEtat(Emprunte); // on precise que ce livre est desormais emprunte                 
            }            
            else {
                // cas qui n'a pas ete specifie
                throw std::runtime_error(" Livre dont on est proprio mais il est prete autrepart OU livre qui nous a ete prete donc il est dans notre base de donnee mais n'est plus chez nous \n ");
            }
            }
            catch (const std::exception& e) {
                    std::cout << "Exception Capturee: " << e.what() << "\n";
                } }


    // pour verifier si notre adherent a emprunte ce livre
    bool AEmprunte (Livre* monLivre) {
        try {
            if (monLivre == nullptr) {
                throw std::runtime_error("Livre = nullptr");
            }
            std::vector<Livre*>& monvecteur = this->getLivresEmpruntes();
            for (int i=0; i<monvecteur.size(); i++) {
                // on veut savoir si il a bien emrunte le livre precis donc on compare les adresses memoires
                if (monvecteur[i] == monLivre) {
                    return true;
                }
            }
            return false;
        }
        catch (const std::exception& e) {
                    std::cout << "Exception Capturee: " << e.what() << "\n";
                    return false;
                }
    }

    bool AEmprunteOuCopie (Livre* monLivre) {
        try {
            if (monLivre == nullptr) {
                throw std::runtime_error("Livre = nullptr");
            }
            std::vector<Livre*>& monvecteur = this->getLivresEmpruntes();
            for (int i=0; i<monvecteur.size(); i++) {
                // on veut savoir si il a bien emrunte le livre precis donc on compare les adresses memoires
                if (*monvecteur[i] == *monLivre) {
                    return true;
                }
            }
            return false;
        }
        catch (const std::exception& e) {
                    std::cout << "Exception Capturee: " << e.what() << "\n";
                    return false;
                }
    }

    void SupprimerLivre(Livre* pmonlivre){
            // on fait  une reference du vecteur pour avoir l'objet monvecteur
            // monvecteur plus facile a utiliser que monDIctionnaire...

            try {
                if (pmonlivre == nullptr){ throw std::runtime_error("pointeur nul");}
                if (this->AEmprunte(pmonlivre) == false) { throw std::runtime_error("probleme : livre pas present dans les emprunts");}
            std::vector<Livre*>& monvecteur = this->getLivresEmpruntes();
            for (int i=0; i< monvecteur.size(); i++ ) {
                // methode dans le cas ou on veut rendre un livre emprunte par notre adherent
                // il va rendre le livre precis 
                // donc on compare les adresses memoires des pointeurs
                if ( (monvecteur[i] != nullptr) && monvecteur[i] == pmonlivre){
                    // on prend le vecteur et onsuprime l'element correspondant
                    // pour cela on utilise un iterateur
                    monvecteur.erase( monvecteur.begin() +i);                    
                }
            }
             }
            catch (const std::exception& e) {
                std::cout<< "Exception Capturee";
            }
        }



    void Rendre (Livre* monLivre) {
        try {
            if (monLivre == nullptr) {
                throw std::runtime_error("Livre = nullptr");
            }
            if ( this->AEmprunte(monLivre) == false) {
                throw std::runtime_error(" l'utilisateur n'a pas emprunte ce livre ou alors un autre exemplaire \n");
            } else {
                monLivre->SetEtat(Libre);
                this->SupprimerLivre(monLivre);             
            }
        }
        catch (const std::exception& e) {
                    std::cout << "Exception Capturee: " << e.what() << "\n";
                }

    }

};
#endif