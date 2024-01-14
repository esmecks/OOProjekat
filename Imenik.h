#include "Kontakt.h"
#ifndef IMENIK_IMENIK
#define IMENIK_IMENIK_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

class Imenik{
	private:
    	std::vector<std::unique_ptr<Kontakt>> kontakti;
	public:
	    void prikaziMeni();
    	void dodajKontakt(const Kontakt& kontakt);
    	void obrisiKontakt(const std::string& brojTelefona);
    	Kontakt traziKontakt(const std::string& brojTelefona)const;
    	void ispisSvihKontakata(const std::string& Datoteka)const;
        void urediKontakt(const std::string& brojTelefona, const Kontakt& uredjeniKontakt);
    	std::vector<Kontakt> filtrirajKontaktePoTipu(TipKontakta tip)const;
    	void sortirajKontakte();
    	void sacuvajKontakteUDatoteku(const std::string& imeDatoteke);
    	void azurirajDatoteku(const std::string& imeDatoteke);
    	void ucitajKontakteIzDatoteke(const std::string& imeDatoteke);
    	void dodajKontaktUTextDatoteku(const Kontakt& kontakt);
    	void obrisiKontaktIzDatoteke(const std::string& ime, const std::string& prezime);
    	void urediKontaktUDatoteci(const std::string& ime, const std::string& prezime, const Kontakt& noviPodaci);
    	void sortirajKontakteIPisiUDatoteku(const std::string& izlaznaDatoteka);
    	void ucitajIzDatoteke(const std::string& datoteka);
};
#endif
