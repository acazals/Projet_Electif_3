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

    std::vector<Livre*> livres1;
    livres1.push_back(new BandeDessinee(101, "Hergé", "Casterman", 123456789, "Tout public", Libre, "Hergé"));
    livres1.push_back(new BandeDessinee(102, "Franquin", "Dupuis", 234567890, "Adolescents", Libre, "Franquin"));
    livres1.push_back(new Roman(201, "Victor Hugo", "Gallimard", 112233445, "Tout public", Emprunte, "Classique"));
    livres1.push_back(new Roman(202, "George Orwell", "Secker & Warburg", 223344556, "Adolescents", Prete, "Dystopie"));
    
    std::map<Booktype, std::vector<Livre*>> dictionnaire1;
    for (Livre* livre : livres1) {
        dictionnaire1[livre->getBT()].push_back(livre);
    }

    // Dictionnaire 2: Bibliothèque 2
    std::vector<Livre*> livres2;
    livres2.push_back(new BandeDessinee(103, "Goscinny", "Dargaud", 345678901, "Enfants", Libre, "Uderzo"));
    livres2.push_back(new BandeDessinee(104, "Moebius", "Les Humanoïdes", 456789012, "Adultes", Libre, "Moebius"));
    livres2.push_back(new Roman(203, "Flaubert", "Folio", 334455667, "Tout public", Libre, "Classique"));
    livres2.push_back(new Roman(204, "J.K. Rowling", "Bloomsbury", 445566778, "Enfants", Emprunte, "Fantastique"));
    
    std::map<Booktype, std::vector<Livre*>> dictionnaire2;
    for (Livre* livre : livres2) {
        dictionnaire2[livre->getBT()].push_back(livre);
    }

    // Dictionnaire 3: Bibliothèque 3
    std::vector<Livre*> livres3;
    livres3.push_back(new BandeDessinee(105, "Morris", "Dupuis", 567890123, "Tout public", Emprunte, "Morris"));
    livres3.push_back(new BandeDessinee(106, "Peyo", "Dupuis", 678901234, "Tout public", Libre, "Peyo"));
    livres3.push_back(new Roman(205, "Albert Camus", "Gallimard", 556677889, "Adultes", Prete, "Existentialisme"));
    livres3.push_back(new Roman(206, "Hemingway", "Scribner", 667788990, "Adultes", Libre, "Drame"));

    std::map<Booktype, std::vector<Livre*>> dictionnaire3;
    for (Livre* livre : livres3) {
        dictionnaire3[livre->getBT()].push_back(livre);
    }

    Bibliotheque bibliotheque1(1, "Bibliothèque Municipale", "123 Rue de Paris", dictionnaire1, 10);
    Bibliotheque bibliotheque2(2, "Bibliothèque Centrale", "45 Avenue des Champs", dictionnaire2, 5);
    Bibliotheque bibliotheque3(3, "Bibliothèque Universitaire", "678 Rue des Sciences", dictionnaire3, 7);

    
    
    
    // bibliotheque3.Afficher(BT_none);

    
    // Livre *pLivre = livres3[0];
    // bibliotheque3.SupprimerLivre(pLivre);
    // std::cout<< "SUPPRESSION" << "\n";
    // bibliotheque3.Afficher(BT_none);
    // suppression marche bien!

    // bibliotheque1.Afficher();
    // bibliotheque1.AjouterLivre(livres2[0]);
    // std::cout<< "AJOUT" << "\n";
    // bibliotheque1.Afficher(); // la fonction ajout marche bien !

    bibliotheque2.Afficher(BT_bandeDessinee);
    bibliotheque1.Demander(livres2[0], bibliotheque2);
    std::cout<< "EMPRUNT" << "\n";
    bibliotheque2.Afficher(BT_bandeDessinee);
;
    
    return 0;
}