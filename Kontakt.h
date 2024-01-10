#include "TipKontakta.h"
#ifndef IMENIK_KONTAKT
#define IMENIK_KONTAKT_H
#include<iostream>

class Kontakt{
	private:
    	std::string ime, prezime, brojTelefona, adresa;
    	TipKontakta tip;
	public:
    	Kontakt(const std::string& ime, const std::string& prezime, const std::string& brojTelefona, const std::string& adresa, TipKontakta tip);
		const std::string& dajIme() const;
    	const std::string& dajPrezime() const;
    	const std::string& dajBrojTelefona() const;
    	const std::string& dajAdresu() const;
    	TipKontakta dajTip() const;
		void ispisiKontakt() const;
};

#endif
