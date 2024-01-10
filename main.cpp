#include "Imenik.h"
#include<iostream>
#include<vector>

int main(){
	
    Imenik imenik;
    Kontakt kontakt1("Suljo", "Zmaj", "064-923-71/30", "Prve Zenicke Brigade", TipKontakta::Licni);
    Kontakt kontakt2("Haso", "Hasic", "060-654-32/10", "Mejdandzik", TipKontakta::Poslovni);
    Kontakt kontakt3("Fata", "Bivsa", "062-657-732", "Potok", TipKontakta::Licni);

    imenik.dodajKontakt(kontakt1);
    imenik.dodajKontakt(kontakt2);
    imenik.dodajKontakt(kontakt3);

    imenik.ispisSvihKontakata();

    std::cout<<"\nPretrazuje se kontakt sa sljedecim brojem telefona 060-654-32/10:\n";
    Kontakt nadjeniKontakt=imenik.traziKontakt("060-654-32/10");
    if(nadjeniKontakt.dajTip()!=TipKontakta::Ostalo){
        nadjeniKontakt.ispisiKontakt();
    } 
	else{
        std::cout<<"Kontakt nije pronadjen.\n";
    }

    std::cout<<"\nFiltriranje kontakata po tipu Licni:\n";
    std::vector<Kontakt> filtriraniKontakti=imenik.filtrirajKontaktePoTipu(TipKontakta::Licni);
    for(const auto& kontakt : filtriraniKontakti){
        kontakt.ispisiKontakt();
    }

    std::cout<<"\nUredi kontakt sa sljedecim brojem telefona 062-456-789:\n";
    Kontakt urediKontakt("Suljo", "Zmaj", "062-456-789", "Prve Zenicke Brigade", TipKontakta::Licni);
    imenik.urediKontakt("062-456-789", urediKontakt);

    std::cout<<"\nSortiranje kontakata:\n";
    imenik.sortirajKontakte();
    imenik.ispisSvihKontakata();

    std::cout<<"\nBrise se kontakt sa sljedecim brojem 064-923-71/30:\n";
    imenik.obrisiKontakt("064-923-71/30");
    imenik.ispisSvihKontakata();

    return 0;
}
