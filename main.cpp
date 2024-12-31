#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <vector>

//#include "bibliotheque.h"
#include "biblio2.h"
#include "livre.h"
#include "BandeDessinee.h"
#include "PieceTheatre.h"
#include "Roman.h"
#include "ReceuilPoesie.h"
#include "Album.h"



int main () {
    
    
    
    // Création des livres
    std::vector<Livre*> livres;
    livres.push_back(new BandeDessinee(101, "Hergé", "Casterman", 123456789, "Tout public", Libre, "Hergé"));
    livres.push_back(new BandeDessinee(102, "Franquin", "Dupuis", 234567890, "Adolescents", Libre, "Franquin"));
    livres.push_back(new Roman(201, "Victor Hugo", "Gallimard", 112233445, "Tout public", Emprunte, "Classique"));
    livres.push_back(new Roman(202, "George Orwell", "Secker & Warburg", 223344556, "Adolescents", Prete, "Dystopie"));
    // Ajouter les autres livres ici...

    // Créer un dictionnaire de livres par type
    std::map<Booktype, std::vector<Livre*>> dictionnaire;
    for (Livre* livre : livres) {
        dictionnaire[livre->getBT()].push_back(livre);
    }

    // Créer la bibliothèque
    Bibliotheque mabibliotheque = Bibliotheque(1, "Bibliothèque Municipale", "123 Rue de Paris", dictionnaire, 10);

    // Ajouter des livres supplémentaires à la bibliothèque si nécessaire
    // bibliotheque.AjouterLivre(...);

    // Affichage des livres dans la bibliothèque
    mabibliotheque.Afficher(BT_none);

    // Libération de la mémoire
    for (Livre* livre : livres) {
        delete livre;
    }
    return 0;
}