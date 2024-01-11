#include<iostream>
#include<vector>
#include<algorithm>
#include<memory>
#include<fstream>
#include<sstream>
#include"Imenik.h"

void Imenik::prikaziMeni(){
    std::cout << "-------------------Menu--------------------\n";
    std::cout << "1. Dodaj kontakt\n";
    std::cout << "2. Obrisi kontakt\n";
    std::cout << "3. Pronadji kontakt\n";
    std::cout << "4. Ispisi sve kontakte\n";
    std::cout << "5. Uredi kontakt\n";
    std::cout << "6. Filtriraj kontakte po tipu\n";
    std::cout << "7. Sortiraj kontakte\n";
    std::cout << "8. Sacuvaj kontakte u datoteku\n";
    std::cout << "9. Azuriraj kontakte u datoteci\n";
    std::cout << "10. Ucitaj kontakte iz datoteke\n";
    std::cout << "11. Izlaz\n";
    std::cout << "--------------Izaberite opciju?---------------\n";
}

void Imenik::dodajKontakt(const Kontakt& kontakt){
    std::unique_ptr<Kontakt> noviKontakt = std::make_unique<Kontakt>(kontakt);
    kontakti.push_back(std::move(noviKontakt));
}

void Imenik::obrisiKontakt(const std::string& brojTelefona){
    kontakti.erase(std::remove_if(kontakti.begin(), kontakti.end(), [brojTelefona](const std::unique_ptr<Kontakt>& kontakt_ptr){
        return kontakt_ptr->dajBrojTelefona() == brojTelefona; }),
        kontakti.end());
}

void Imenik::sortirajKontakte(){
    std::sort(kontakti.begin(), kontakti.end(), [](const std::unique_ptr<Kontakt>& a, const std::unique_ptr<Kontakt>& b){
        return a->dajPrezime() < b->dajPrezime();
    });
}

Kontakt Imenik::traziKontakt(const std::string& brojTelefona) const{
    auto it=std::find_if(kontakti.begin(), kontakti.end(), [brojTelefona](const std::unique_ptr<Kontakt>& ptr){
        return ptr->dajBrojTelefona() == brojTelefona;
    });
    if(it != kontakti.end()){
        return *(*it);
    }else{
        return Kontakt("", "", "", "", TipKontakta::Ostalo);
    }
}

void Imenik::urediKontakt(const std::string& brojTelefona, const Kontakt& uredjeniKontakt){
    auto it=std::find_if(kontakti.begin(), kontakti.end(), [brojTelefona](const std::unique_ptr<Kontakt>& ptr){
        return ptr->dajBrojTelefona()==brojTelefona;
    });
    if (it!=kontakti.end()){
        *(*it)=uredjeniKontakt;
    }else{
        std::cout << "Kontakt koji zelite urediti nije pronadjen.\n";
    }
}

void Imenik::ispisSvihKontakata() const{
    std::cout << "Svi kontakti:\n";
    for (const auto& kontakt_ptr : kontakti){
        kontakt_ptr->ispisiKontakt();
    }
}

std::vector<Kontakt> Imenik::filtrirajKontaktePoTipu(TipKontakta tip) const{
    std::vector<Kontakt> filtriraniKontakti;
    std::transform(kontakti.begin(), kontakti.end(), std::back_inserter(filtriraniKontakti), [tip](const std::unique_ptr<Kontakt>& kontakt_ptr){
        return *kontakt_ptr;
    });
    filtriraniKontakti.erase(std::remove_if(filtriraniKontakti.begin(), filtriraniKontakti.end(), [tip](const Kontakt& kontakt){
        return kontakt.dajTip() != tip;
    }), filtriraniKontakti.end());
    return filtriraniKontakti;
}

void Imenik::sacuvajKontakteUDatoteku(const std::string& imeDatoteke){
    std::ofstream file(imeDatoteke);
    if(file.is_open()){
            for (const auto& kontakt : kontakti){
            file << kontakt->dajIme() << "," << kontakt->dajPrezime() << "," << kontakt->dajBrojTelefona() << "," << kontakt->dajAdresu() << "," << static_cast<int>(kontakt->dajTip()) << "\n";
        }
        std::cout << "Kontakti su uspjesno spremljeni u datoteku " << imeDatoteke << std::endl;
        file.close();
    }
    else{
        std::cout << "Nije moguce otvoriti datoteku za pisanje." << std::endl;
    }
}

void Imenik::azurirajDatoteku(const std::string& imeDatoteke){
    std::ofstream file(imeDatoteke);
    if(file.is_open()){
        for(const auto& kontakt_ptr : kontakti){
            file << kontakt_ptr->dajIme() << ","
                 << kontakt_ptr->dajPrezime() << ","
                 << kontakt_ptr->dajBrojTelefona() << ","
                 << kontakt_ptr->dajAdresu() << ","
                 << static_cast<int>(kontakt_ptr->dajTip()) << "\n";
        }
        std::cout << "Podaci su uspjesno azurirani u datoteci " << imeDatoteke << std::endl;
        file.close();
    }
    else{
        std::cout << "Nije moguce otvoriti datoteku za pisanje." << std::endl;
    }
}

void Imenik::ucitajKontakteIzDatoteke(const std::string& imeDatoteke){
    std::ifstream datoteka(imeDatoteke);
    if (datoteka.is_open()){
        std::string linija;
        while (std::getline(datoteka, linija)){
            std::istringstream iss(linija);
            std::string ime, prezime, brojTelefona, adresa;
            int tip;

            std::getline(iss, ime, ',');
            std::getline(iss, prezime, ',');
            std::getline(iss, brojTelefona, ',');
            std::getline(iss, adresa, ',');
            iss >> tip;

            TipKontakta tipKontakta = static_cast<TipKontakta>(tip);

            Kontakt noviKontakt(ime, prezime, brojTelefona, adresa, tipKontakta);
            dodajKontakt(noviKontakt);
        }
        datoteka.close();
        std::cout << "Kontakti su uspjesno ucitani iz datoteke.\n";
    }
    else{
        std::cout << "Nije moguce otvoriti datoteku za citanje.\n";
    }
}


