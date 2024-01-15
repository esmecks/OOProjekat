#include<iostream>
#include<vector>
#include<algorithm>
#include<memory>
#include<fstream>
#include<sstream>
#include <iomanip>
#include"Imenik.h"
#include"TipKontakta.h"


void Imenik::prikaziMeni(){
    std::cout << "-------------------Menu--------------------\n";
    std::cout << "1. Dodaj kontakt\n";
    std::cout << "2. Obrisi kontakt\n";
    std::cout << "3. Pronadji kontakt\n";
    std::cout << "4. Ispisi sve kontakte\n";
    std::cout << "5. Uredi kontakt\n";
    std::cout << "6. Filtriraj kontakte po tipu\n";
    std::cout << "7. Sortiraj kontakte\n";
    std::cout << "9. Azuriraj kontakte u datoteci\n";
    std::cout << "11. Izlaz\n";
    std::cout << "--------------Izaberite opciju?---------------\n";
}

void Imenik::dodajKontakt(const Kontakt& kontakt){
    std::unique_ptr<Kontakt> noviKontakt = std::make_unique<Kontakt>(kontakt);
    kontakti.push_back(std::move(noviKontakt));


}
void Imenik::dodajKontaktUTextDatoteku(const Kontakt& kontakt) {
        std::unique_ptr<Kontakt> noviKontakt = std::make_unique<Kontakt>(kontakt);
        kontakti.push_back(std::move(noviKontakt));

        // Otvorite datoteku u načinu dodavanja
        std::ofstream datoteka("imenik.txt", std::ios_base::app);

        // Provjerite jesu li svi podaci unutar datoteke
        if (datoteka.is_open()) {
            datoteka << "Ime: " << kontakt.dajIme() << "\n";
            datoteka << "Prezime: " << kontakt.dajPrezime() << "\n";
            datoteka << "Broj telefona: " << kontakt.dajBrojTelefona() << "\n";
            datoteka << "Adresa: " << kontakt.dajAdresu() << "\n";

            datoteka << "Tip kontakta: ";
            switch (kontakt.dajTip()) {
                case TipKontakta::Poslovni:
                    datoteka << "Poslovni\n";
                    break;
                case TipKontakta::Licni:
                    datoteka << "Licni\n";
                    break;
                case TipKontakta::Ostalo:
                    datoteka << "Ostalo\n";
                    break;

            }

            datoteka << "------------------------------\n";

            // Zatvorite datoteku
            datoteka.close();
        } else {
            std::cerr << "Nije moguće otvoriti datoteku za pisanje." << std::endl;
        }
    }

void Imenik::obrisiKontaktIzDatoteke(const std::string& ime, const std::string& prezime) {
        std::ifstream ulaznaDatoteka("imenik.txt");
        std::ofstream izlaznaDatoteka("imenik_temp.txt");

        if (!ulaznaDatoteka.is_open() || !izlaznaDatoteka.is_open()) {
            std::cerr << "Nije moguće otvoriti datoteke za čitanje ili pisanje." << std::endl;
            return;
        }

        std::string linija;
        bool obrisan = false;

        while (std::getline(ulaznaDatoteka, linija)) {
            if (linija.find("Ime: " + ime) != std::string::npos &&
                std::getline(ulaznaDatoteka, linija) && // Preskoči liniju s prezimenom
                linija.find("Prezime: " + prezime) != std::string::npos) {
                // Preskoči i zanemari ostale informacije o kontaktu
                for (int i = 0; i < 4; ++i) {
                    std::getline(ulaznaDatoteka, linija);
                }
                obrisan = true;
            } else {
                // Ako nije kontakt koji želite izbrisati, zapišite ga u izlaznu datoteku
                izlaznaDatoteka << linija << '\n';
            }
        }

        if (!obrisan) {
            std::cerr << "Kontakt nije pronađen u datoteci." << std::endl;
        }

        // Zatvorite datoteke
        ulaznaDatoteka.close();
        izlaznaDatoteka.close();

        // Zamijenite originalnu datoteku s privremenom datotekom
        std::remove("imenik.txt");
        std::rename("imenik_temp.txt", "imenik.txt");

}

void Imenik::ucitajIzDatoteke(const std::string& datoteka) {
    std::ifstream ulaz(datoteka);
    if (!ulaz.is_open()) {
        std::cerr << "Nije moguće otvoriti datoteku za čitanje: " << datoteka << std::endl;
        return;
    }

    std::string linija;
    while (std::getline(ulaz, linija)) {
        std::string ime, prezime, broj, adresa, tipKontakta;


        // Učitavanje imena
        if (linija.find("Ime: ") != std::string::npos) {
            ime = linija.substr(5);
        }

        // Učitavanje prezimena
        std::getline(ulaz, linija);
        if (linija.find("Prezime: ") != std::string::npos) {
            prezime = linija.substr(9);
        }

        // Učitavanje broja telefona
        std::getline(ulaz, linija);
        if (linija.find("Broj telefona: ") != std::string::npos) {
            broj = linija.substr(15);
        }

        // Učitavanje adrese
        std::getline(ulaz, linija);
        if (linija.find("Adresa: ") != std::string::npos) {
            adresa = linija.substr(8);
        }

        // Učitavanje tipa kontakta
        std::getline(ulaz, linija);
        if (linija.find("Tip kontakta: ") != std::string::npos) {
            tipKontakta = linija.substr(14);
        }

        // Učitavanje tipa kontakta
        std::getline(ulaz, linija);
        if (linija.find("Tip kontakta: ") != std::string::npos) {
            tipKontakta = linija.substr(14);
        }

       TipKontakta tip;
       if (tipKontakta == "Poslovni") {
        tip = TipKontakta::Poslovni;
       } else if (tipKontakta == "Licni") {
        tip = TipKontakta::Licni;
       } else if (tipKontakta == "Ostalo") {
        tip = TipKontakta::Ostalo;
       } else {
        tip = TipKontakta::Ostalo;
       }

       Kontakt kontakt(ime, prezime, broj, adresa, tip);
       kontakti.push_back(std::make_unique<Kontakt>(kontakt));
       }
       ulaz.close();
}

void Imenik::sortirajKontakteIPisiUDatoteku(const std::string& izlaznaDatoteka) {
    // Sortiranje kontakata po prezimenu
    std::sort(kontakti.begin(), kontakti.end(), [](const std::unique_ptr<Kontakt>& a, const std::unique_ptr<Kontakt>& b) {
        return a->dajPrezime() < b->dajPrezime();
    });

    // Ispis sortiranih kontakata u novu datoteku
    std::ofstream izlaznaDatotekaStream(izlaznaDatoteka);
    if (izlaznaDatotekaStream.is_open()) {
        for (const auto& kontakt : kontakti) {
            izlaznaDatotekaStream << "Ime: " << kontakt->dajIme() << "\n";
            izlaznaDatotekaStream << "Prezime: " << kontakt->dajPrezime() << "\n";
            izlaznaDatotekaStream << "Broj telefona: " << kontakt->dajBrojTelefona() << "\n";
            izlaznaDatotekaStream << "Adresa: " << kontakt->dajAdresu() << "\n";
            izlaznaDatotekaStream << "Tip kontakta: " << kontakt->dajTip() << "\n";
            izlaznaDatotekaStream << "------------------------------\n";
        }
        izlaznaDatotekaStream.close();
    } else {
        std::cerr << "Nije moguće otvoriti izlaznu datoteku za pisanje." << std::endl;
    }
}

void Imenik::obrisiKontakt(const std::string& brojTelefona){
    auto it = std::remove_if(kontakti.begin(), kontakti.end(), [brojTelefona](const std::unique_ptr<Kontakt>& kontakt_ptr) {
        return kontakt_ptr->dajBrojTelefona() == brojTelefona;
    });

    if (it != kontakti.end()) {
        kontakti.erase(it, kontakti.end());
    } else {
        throw BrojNijePronadjenIznimka("Kontakt nije pronađen.");
    }
}

/*void Imenik::sortirajKontakte(){
    std::sort(kontakti.begin(), kontakti.end(), [](const std::unique_ptr<Kontakt>& a, const std::unique_ptr<Kontakt>& b){
        return a->dajPrezime() < b->dajPrezime();
    });
}*/

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

void Imenik::ispisSvihKontakata(const std::string& Datoteka) const{
    std::ifstream datoteka(Datoteka);

        if (!datoteka.is_open()) {
            std::cerr << "Nije moguce otvoriti datoteku za citanje." << std::endl;
            return;
        }

        std::string linija;

        std::cout<<"\nKontakti:\n\n";
        while (std::getline(datoteka, linija)) {
            if (linija == "------------------------------") {

                std::cout << std::endl;
            } else {

                std::cout << linija << std::endl;
            }
        }

        datoteka.close();

}

void Imenik::urediKontaktUDatoteci(const std::string& ime, const std::string& prezime, const Kontakt& noviPodaci) {
        std::ifstream ulaznaDatoteka("imenik.txt");
        std::ofstream privremenaDatoteka("imenik_temp.txt");

        if (!ulaznaDatoteka.is_open() || !privremenaDatoteka.is_open()) {
            std::cerr << "Nije moguće otvoriti datoteke za čitanje ili pisanje." << std::endl;
            return;
        }

        std::string linija;
        bool kontaktPronaden = false;

        while (std::getline(ulaznaDatoteka, linija)) {
            if (linija.find("Ime: " + ime) != std::string::npos &&
                std::getline(ulaznaDatoteka, linija) && // Preskoči liniju s prezimenom
                linija.find("Prezime: " + prezime) != std::string::npos) {
                // Pronađen kontakt koji se želi urediti
                kontaktPronaden = true;

                // Zamijeni informacije o kontaktu s novim podacima
                privremenaDatoteka << "Ime: " << noviPodaci.dajIme() << "\n";
                privremenaDatoteka << "Prezime: " << noviPodaci.dajPrezime() << "\n";
                privremenaDatoteka << "Broj telefona: " << noviPodaci.dajBrojTelefona() << "\n";
                privremenaDatoteka << "Adresa: " << noviPodaci.dajAdresu() << "\n";
                privremenaDatoteka << "Tip kontakta: ";

                switch (noviPodaci.dajTip()) {
                    case TipKontakta::Poslovni:
                        privremenaDatoteka << "Poslovni\n";
                        break;
                    case TipKontakta::Licni:
                        privremenaDatoteka << "Licni\n";
                        break;
                    case TipKontakta::Ostalo:
                        privremenaDatoteka << "Ostalo\n";
                        break;

                }

                privremenaDatoteka << "------------------------------\n";

                // Preskoči originalne informacije o kontaktu
                for (int i = 0; i < 4; ++i) {
                    std::getline(ulaznaDatoteka, linija);
                }
            } else {
                // Ako nije kontakt koji se želi urediti, zapiši ga u privremenu datoteku
                privremenaDatoteka << linija << '\n';
            }
        }

        if (!kontaktPronaden) {
            std::cerr << "Kontakt nije pronađen u datoteci." << std::endl;
        }

        // Zatvori datoteke
        ulaznaDatoteka.close();
        privremenaDatoteka.close();

        // Zamijeni originalnu datoteku s privremenom datotekom
        std::remove("imenik.txt");
        std::rename("imenik_temp.txt", "imenik.txt");
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

bool Imenik::operator==(const Imenik& nessta) const {
    return kontakti == nessta.kontakti;
}

