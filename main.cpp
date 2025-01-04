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
#include "Adherent.h"



int main () {

   // Création des dictionnaires vides
    std::map<Booktype, std::vector<Livre*>> dictionnaire1;
    std::map<Booktype, std::vector<Livre*>> dictionnaire2;
    std::map<Booktype, std::vector<Livre*>> dictionnaire3;

    // Création des bibliothèques
    Bibliotheque bibliotheque1(1, "Bibliothèque Municipale", "123 Rue de Paris", dictionnaire1, 10);
    Bibliotheque bibliotheque2(2, "Bibliothèque Centrale", "45 Avenue des Champs", dictionnaire2, 5);
    Bibliotheque bibliotheque3(3, "Bibliothèque Universitaire", "678 Rue des Sciences", dictionnaire3, 7);

    // Création des livres
    Livre* Biblio1_BD1 = new BandeDessinee(101, "Hergé", "Casterman", 123456789, "Tout public", Libre, "Hergé");
    Livre* Biblio1_BD2 = new BandeDessinee(102, "Franquin", "Dupuis", 234567890, "Adolescents", Libre, "Franquin");
    Livre* Biblio1_Roman1 = new Roman(201, "Victor Hugo", "Gallimard", 112233445, "Tout public", Emprunte, "Classique");
    Livre* Biblio1_Roman2 = new Roman(202, "George Orwell", "Secker & Warburg", 223344556, "Adolescents", Libre, "Dystopie");

    Livre* Biblio2_BD1 = new BandeDessinee(103, "Goscinny", "Dargaud", 345678901, "Enfants", Libre, "Uderzo");
    Livre* Biblio2_BD2 = new BandeDessinee(104, "Moebius", "Les Humanoïdes", 456789012, "Adultes", Libre, "Moebius");
    Livre* Biblio2_Roman1 = new Roman(203, "Flaubert", "Folio", 334455667, "Tout public", Libre, "Classique");
    Livre* Biblio2_Roman2 = new Roman(204, "J.K. Rowling", "Bloomsbury", 445566778, "Enfants", Emprunte, "Fantastique");

    Livre* Biblio3_BD1 = new BandeDessinee(105, "Morris", "Dupuis", 567890123, "Tout public", Emprunte, "Morris");
    Livre* Biblio3_BD2 = new BandeDessinee(106, "Peyo", "Dupuis", 678901234, "Tout public", Libre, "Peyo");
    Livre* Biblio3_Roman1 = new Roman(205, "Albert Camus", "Gallimard", 556677889, "Adultes", Libre, "Existentialisme");
    Livre* Biblio3_Roman2 = new Roman(206, "Hemingway", "Scribner", 667788990, "Adultes", Libre, "Drame");

    // Ajout des livres aux bibliothèques
    bibliotheque1.AjouterLivre(Biblio1_BD1);
    bibliotheque1.AjouterLivre(Biblio1_BD2);
    bibliotheque1.AjouterLivre(Biblio1_Roman1);
    bibliotheque1.AjouterLivre(Biblio1_Roman2);

    bibliotheque2.AjouterLivre(Biblio2_BD1);
    bibliotheque2.AjouterLivre(Biblio2_BD2);
    bibliotheque2.AjouterLivre(Biblio2_Roman1);
    bibliotheque2.AjouterLivre(Biblio2_Roman2);

    bibliotheque3.AjouterLivre(Biblio3_BD1);
    bibliotheque3.AjouterLivre(Biblio3_BD2);
    bibliotheque3.AjouterLivre(Biblio3_Roman1);
    bibliotheque3.AjouterLivre(Biblio3_Roman2);

    Adherent adherent1("Dupont", "Jean", 1, &bibliotheque1);
    Adherent adherent2("Martin", "Claire", 2, &bibliotheque1);
    Adherent adherent3("Lemoine", "Paul", 3, &bibliotheque2);
    Adherent adherent4("Durand", "Sophie", 4, &bibliotheque2);
    Adherent adherent5("Bertrand", "Pierre", 5, &bibliotheque3);


    

    
    // Livre *pLivre = livres3[0];
    // bibliotheque3.SupprimerLivre(pLivre);
    // std::cout<< "SUPPRESSION" << "\n";
    // bibliotheque3.Afficher(BT_none);
    // suppression marche bien!

    // bibliotheque1.Afficher(BT_bandeDessinee);
    // bibliotheque1.AjouterLivre(livres2[0]);
    // std::cout<< "AJOUT" << "\n";
    // bibliotheque1.Afficher(BT_bandeDessinee); // la fonction ajout marche bien !

    // // bibliotheque2.Afficher(BT_bandeDessinee);
    bibliotheque1.Demander(Biblio2_BD1, bibliotheque2);
    // // std::cout<< "EMPRUNT" << "\n";
    // // bibliotheque2.Afficher(BT_bandeDessinee); // la fonction pret entre bibliotheques marche bien !!


    adherent1.Emprunter(Biblio2_BD1);
    adherent1.afficher();
    adherent1.Rendre(Biblio2_BD1);
    // // test de la fonction rendre
    bibliotheque1.Rendre(Biblio2_BD1);
    std::cout<< "RETOUR" << "\n \n \n";
    bibliotheque1.Afficher(BT_bandeDessinee)


    
    


    
   

;
    
    return 0;
}