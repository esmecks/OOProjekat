#include "Kontakt.h"
#ifndef IMENIK_IMENIK
#define IMENIK_IMENIK_H
#include <iostream>
#include <vector>
#include <algorithm>

class Imenik{
	private:
    	std::vector<Kontakt> kontakti;
	public:
    	void dodajKontakt(const Kontakt& kontakt);
    	void obrisiKontakt(const std::string& brojTelefona);
    	void sortirajKontakte();
    	Kontakt traziKontakt(const std::string& brojTelefona)const;
    	void grupniKontakti();
    	void urediKontakt(const std::string& brojTelefona, const Kontakt& uredjeniKontakt);
    	void ispisSvihKontakata()const;
    	std::vector<Kontakt> filtrirajKontaktePoTipu(TipKontakta tip)const;
    	void ispisiNapomenu()const;
};

#endif
