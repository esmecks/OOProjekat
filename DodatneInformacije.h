#pragma once
#include "Kontakt.h"

class DodatneInformacije : public Kontakt {
private:
    std::string email;
    std::string rodjendan;

public:
    DodatneInformacije(const std::string& ime, const std::string& prezime, const std::string& brojTelefona,
                       const std::string& adresa, const std::string& email, const std::string& rodjendan);


    void unosInformacija();
    virtual void ispisiInformacije() const override;

    ~DodatneInformacije();
};
