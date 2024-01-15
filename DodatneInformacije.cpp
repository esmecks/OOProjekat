#include "DodatneInformacije.h"
#include <iostream>

DodatneInformacije::DodatneInformacije(const std::string& ime, const std::string& prezime, const std::string& brojTelefona,
                                       const std::string& adresa, const std::string& email, const std::string& rodjendan)
    : Kontakt(ime, prezime, brojTelefona, adresa, TipKontakta::Licni), email(email), rodjendan(rodjendan) {}


void DodatneInformacije::unosInformacija() {
    std::cout << "Unesite e-mail: ";
    std::cin >> email;
    std::cout << "Unesite rodjendan: ";
    std::cin >> rodjendan;
}

void DodatneInformacije::ispisiInformacije() const {
    std::cout << "E-mail: " << email << std::endl;
    std::cout << "Rodjendan: " << rodjendan << std::endl;
}
DodatneInformacije::~DodatneInformacije() {

}
