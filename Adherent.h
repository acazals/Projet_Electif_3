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


    void Emprunter (Livre* monLivre) {
        try {
            // gestion des erreurs 
            if (monLivre == nullptr) {
                throw std::runtime_error("Livre = nullptr");
            }
            // livre= nullptr
            if (this->NbEmprunts() >= this->getMaBiblio()->getMax()){
                throw std::runtime_error("TROP DE LIVRES DEJA EMPRUNTES");
            } // trop de livres deja empruntes
            if (this->getMaBiblio()->ContientLivre(monLivre) == false){
                throw std::runtime_error("Livre pas dans la biblio");
            } // probleme : pas dans la biblio
            if (monLivre->EstLibre() == false) {
                throw std::runtime_error("erreur : livre deja emprunte");
                // livre qui a deja ete emprunte
            } if(monLivre->getEstPreteAutreBiblio() == true && monLivre->getEmprunteuse() != this->getMaBiblio()) {
                throw std::runtime_error("Erreur : Le livre est prêté à une autre bibliothèque" );
                // livre qui est prete mais pas chez nous : il a ete chez nous avant mais desormais est prete autre part
            } else {
                this->LivresEmpruntes.push_back(monLivre); // on ajoute le livre dans nos livres empruntes
                monLivre->SetEtat(Emprunte); // on precise que ce livre est desormais emprunte
            }
        }
        catch (const std::exception& e) {
                    std::cout << "Exception Capturee: " << e.what() << "\n";
                }
    }

    bool AEmprunte (Livre* monLivre) {
        try {
            if (monLivre == nullptr) {
                throw std::runtime_error("Livre = nullptr");
            }
            std::vector<Livre*>& monvecteur = this->getLivresEmpruntes();
            for (int i=0; i<monvecteur.size(); i++) {
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

    void SupprimerLivre(Livre* pmonlivre){
            // on fait  une reference du vecteur pour avoir l'objet monvecteur
            // monvecteur plus facile a utiliser que monDIctionnaire...

            try {
                if (pmonlivre == nullptr){ throw std::runtime_error("pointeur nul");}
                if (this->AEmprunte(pmonlivre) == false) { throw std::runtime_error("probleme : livre pas present dans les emprunts");}
            std::vector<Livre*>& monvecteur = this->getLivresEmpruntes();
            for (int i=0; i< monvecteur.size(); i++ ) {
                if ( (monvecteur[i] != nullptr) && *monvecteur[i] == *pmonlivre){
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
                throw std::runtime_error("Livre = nullptr");
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