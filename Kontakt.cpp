#include "Kontakt.h"
#include<fstream>
#include<sstream>
#include "DodatneInformacije.h"

Kontakt::Kontakt(const std::string& ime, const std::string& prezime, const std::string& brojTelefona,
                 const std::string& adresa, TipKontakta tip)
    : ime(ime), prezime(prezime), brojTelefona(brojTelefona), adresa(adresa), tip(tip), dodatneInformacije(nullptr) {}

const std::string& Kontakt::dajIme() const{ return ime; }
const std::string& Kontakt::dajPrezime() const{ return prezime; }
const std::string& Kontakt::dajBrojTelefona() const{ return brojTelefona; }
const std::string& Kontakt::dajAdresu() const{ return adresa; }
TipKontakta Kontakt::dajTip() const{ return tip; }

void Kontakt::ispisiKontakt() const{
    std::cout<<"Ime: "<<ime<<" "<<prezime<<"\n";
    std::cout<<"Telefon: "<<brojTelefona<<"\n";
    std::cout<<"Adresa: "<<adresa<<"\n";
    std::cout<<"Tip: "<<tip<<"\n";
    std::cout<<"-------------------------\n";
}

void Kontakt::ispisiInformacijeUDatoteku(const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << ime << " " << prezime << " " << brojTelefona << " " << adresa << std::endl;
        if (dodatneInformacije) {
            dodatneInformacije->ispisiInformacije();
        }
        file.close();
    } else {
        std::cerr << "Nemoguce otvoriti: " << filename << std::endl;
    }
}

void Kontakt::ispisiInformacije() const {
    std::cout << "Ime: " << ime << std::endl;
    std::cout << "Prezime: " << prezime << std::endl;
    std::cout << "Broj telefona: " << brojTelefona << std::endl;
    std::cout << "Adresa: " << adresa << std::endl;
    if (dodatneInformacije) {
        dodatneInformacije->ispisiInformacije();
    }
}

Kontakt::~Kontakt() {
    delete dodatneInformacije;
}


