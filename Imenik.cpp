#include<iostream>
#include <vector>
#include <algorithm>
#include "Imenik.h"

void Imenik::dodajKontakt(const Kontakt& kontakt){
    kontakti.push_back(kontakt);
}

void Imenik::obrisiKontakt(const std::string& brojTelefona){
    auto it=std::remove_if(kontakti.begin(), kontakti.end(), [brojTelefona](const Kontakt& c){ return c.dajBrojTelefona()==brojTelefona; });
    kontakti.erase(it, kontakti.end());
}

void Imenik::sortirajKontakte(){
    std::sort(kontakti.begin(), kontakti.end(), [](const Kontakt& c1, const Kontakt& c2){ return c1.dajPrezime() < c2.dajPrezime(); });
}

Kontakt Imenik::traziKontakt(const std::string& brojTelefona) const{
    auto it=std::find_if(kontakti.begin(), kontakti.end(), [brojTelefona](const Kontakt& c){ return c.dajBrojTelefona()==brojTelefona; });
    if(it!=kontakti.end()){
        return *it;
    }
	else{
        return Kontakt("", "", "", "", TipKontakta::Ostalo);
    }
}

void Imenik::grupniKontakti() {
    std::cout<<"Grupni kontakti... (nije implementirano)\n";
}

void Imenik::urediKontakt(const std::string& brojTelefona, const Kontakt& uredjeniKontakt){
    auto it=std::find_if(kontakti.begin(), kontakti.end(), [brojTelefona](const Kontakt& c){ return c.dajBrojTelefona()==brojTelefona; });
    if(it!=kontakti.end()){
        *it=uredjeniKontakt;
    }
	else{
        std::cout<<"Kontakt koji zelite urediti nije pronadjen.\n";
    }
}

void Imenik::ispisSvihKontakata()const{
    std::cout<<"Svi kontakti:\n";
    for(const auto& kontakt : kontakti){
        kontakt.ispisiKontakt();
    }
}

std::vector<Kontakt> Imenik::filtrirajKontaktePoTipu(TipKontakta tip)const{
    std::vector<Kontakt> filtriraniKontakti;
    std::copy_if(kontakti.begin(), kontakti.end(), std::back_inserter(filtriraniKontakti), [tip](const Kontakt& c) { return c.dajTip()==tip; });
    return filtriraniKontakti;
}

void Imenik::ispisiNapomenu()const{
    std::cout<<"Ispis napomena... (nije implementirano)\n";
}
