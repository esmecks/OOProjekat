#include "Kontakt.h"
#include<iostream>

Kontakt::Kontakt(const std::string& ime, const std::string& prezime, const std::string& brojTelefona, const std::string& adresa, TipKontakta tip)
    : ime(ime), prezime(prezime), brojTelefona(brojTelefona), adresa(adresa), tip(tip){}

const std::string& Kontakt::dajIme() const{ return ime; }
const std::string& Kontakt::dajPrezime() const{ return prezime; }
const std::string& Kontakt::dajBrojTelefona() const{ return brojTelefona; }
const std::string& Kontakt::dajAdresu() const{ return adresa; }
TipKontakta Kontakt::dajTip() const{ return tip; }

void Kontakt::ispisiKontakt() const{
    std::cout<<"Ime: "<<ime<<" "<<prezime<<"\n";
    std::cout<<"Telefon: "<<brojTelefona<<"\n";
    std::cout<<"Adresa: "<<adresa<<"\n";
    std::cout<<"Tip: ";
    switch(tip){
        case TipKontakta::Poslovni:
            std::cout<<"Poslovni\n";
            break;
        case TipKontakta::Licni:
            std::cout<<"Licni\n";
            break;
        case TipKontakta::Ostalo:
            std::cout<<"Ostalo\n";
            break;
    }
    std::cout<<"-------------------------\n";
}
