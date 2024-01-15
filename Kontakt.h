#pragma once
#include <iostream>
#include <string>
#include<fstream>
#include<sstream>
#include "TipKontakta.h"

class DodatneInformacije;

class Kontakt {
private:
    std::string ime, prezime, brojTelefona, adresa;
    TipKontakta tip;
    DodatneInformacije* dodatneInformacije;

public:
    Kontakt(const std::string& ime, const std::string& prezime, const std::string& brojTelefona,
            const std::string& adresa, TipKontakta tip);

    const std::string& dajIme() const;
    const std::string& dajPrezime() const;
    const std::string& dajBrojTelefona() const;
    const std::string& dajAdresu() const;
    TipKontakta dajTip() const;

    void ispisiKontakt() const;
    virtual void ispisiInformacije() const;
    void ispisiInformacijeUDatoteku(const std::string& filename) const;

    ~Kontakt();
};

