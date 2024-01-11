#include "Imenik.h"
#include<iostream>
#include<vector>

int main(){

    Imenik imenik;

    Kontakt kontakt1("Suljo", "Zmaj", "064-923-71/30", "Prve Zenicke Brigade", TipKontakta::Licni);
    Kontakt kontakt2("Haso", "Hasic", "060-654-32/10", "Mejdandzik", TipKontakta::Poslovni);
    Kontakt kontakt3("Fata", "Bivsa", "062-657-732", "Potok", TipKontakta::Licni);

    imenik.dodajKontakt(kontakt1);
    imenik.dodajKontakt(kontakt2);
    imenik.dodajKontakt(kontakt3);

    int izbor = 0;
    while(izbor != 11){
        imenik.prikaziMeni();
        std::cin >> izbor;

        switch(izbor){
            case 1: {
                std::string ime, prezime, brojTelefona, adresa;
                TipKontakta tip;
                std::cout << "Unesite ime: ";
                std::cin >> ime;
                std::cout << "Unesite prezime: ";
                std::cin >> prezime;
                std::cout << "Unesite broj telefona: ";
                std::cin >> brojTelefona;
                std::cout << "Unesite adresu: ";
                std::cin >> adresa;
                std::cout << "Unesite tip kontakta (0 - Poslovni, 1 - Licni, 2 - Ostalo): ";
                int tipUnos;
                std::cin >> tipUnos;
                tip = static_cast<TipKontakta>(tipUnos);

                Kontakt noviKontakt(ime, prezime, brojTelefona, adresa, tip);
                imenik.dodajKontakt(noviKontakt);

                std::cout << "Kontakt je uspjesno dodan.\n";
                break;
            }
            case 2: {
                std::string brojTelefona;
                std::cout << "Unesite broj telefona za brisanje kontakta: ";
                std::cin >> brojTelefona;
                imenik.obrisiKontakt(brojTelefona);
                std::cout << "Kontakt je uspjesno obrisan.\n";
                break;
            }
            case 3: {
                std::string brojTelefona;
                std::cout << "Unesite broj telefona za pretragu kontakta: ";
                std::cin >> brojTelefona;

                Kontakt nadjeniKontakt = imenik.traziKontakt(brojTelefona);
                if (nadjeniKontakt.dajBrojTelefona() != "") {
                std::cout << "Pronadjen kontakt:\n";
                nadjeniKontakt.ispisiKontakt();
                }
                else {
                      std::cout << "Kontakt nije pronadjen.\n";
                }
                break;
            }
            case 4: {
                imenik.ispisSvihKontakata();
                break;
            }

            case 5: {
                std::string brojTelefona;
                std::cout << "Unesite broj telefona kontakta koji zelite urediti: ";
                std::cin >> brojTelefona;

                Kontakt nadjeniKontakt = imenik.traziKontakt(brojTelefona);
                if (nadjeniKontakt.dajBrojTelefona() != "") {
                std::string ime, prezime, noviBrojTelefona, adresa;
                TipKontakta tip;

                std::cout << "Unesite novo ime: ";
                std::cin >> ime;
                std::cout << "Unesite novo prezime: ";
                std::cin >> prezime;
                std::cout << "Unesite novi broj telefona: ";
                std::cin >> noviBrojTelefona;
                std::cout << "Unesite novu adresu: ";
                std::cin >> adresa;
                std::cout << "Unesite novi tip kontakta (0 - Poslovni, 1 - Licni, 2 - Ostalo): ";
                int tipUnos;
                std::cin >> tipUnos;
                tip = static_cast<TipKontakta>(tipUnos);

                Kontakt uredjeniKontakt(ime, prezime, noviBrojTelefona, adresa, tip);

                imenik.urediKontakt(brojTelefona, uredjeniKontakt);
                std::cout << "Kontakt je uspjesno uredjen.\n";
              }
              else {
                    std::cout << "Kontakt koji zelite urediti nije pronadjen.\n";
              }
              break;
            }
            case 6: {
                int tipUnos;
                std::cout << "Izaberite tip kontakta za filtriranje (0 - Poslovni, 1 - Licni, 2 - Ostalo): ";
                std::cin >> tipUnos;

                TipKontakta izabraniTip = static_cast<TipKontakta>(tipUnos);

                std::vector<Kontakt> filtriraniKontakti = imenik.filtrirajKontaktePoTipu(izabraniTip);
                for (const auto& kontakt:filtriraniKontakti) {
                kontakt.ispisiKontakt();
                }
            break;
            }
            case 7: {
                imenik.sortirajKontakte();
                imenik.ispisSvihKontakata();
            }
            case 8: {
                std::cout << "Unesite ime datoteke za spremanje kontakata: ";
                std::string imeDatoteke;
                std::cin >> imeDatoteke;
                imenik.sacuvajKontakteUDatoteku(imeDatoteke);
                break;
             }
            case 9: {
                std::string imeDatoteke;
                std::cout << "Unesite ime datoteke za azuriranje: ";
                std::cin >> imeDatoteke;
                imenik.azurirajDatoteku(imeDatoteke);
                std::cout << "Podaci su uspjesno azurirani u datoteci " << imeDatoteke << std::endl;
                break;
            }
            case 10: {
                std::cout << "Unesite ime datoteke za ucitavanje kontakata: ";
                std::string imeDatoteke;
                std::cin >> imeDatoteke;
                imenik.ucitajKontakteIzDatoteke(imeDatoteke);
                break;
            }
            case 11: {
                std::cout << "Izlaz iz programa.\n";
                break;
            }
            default: {
                std::cout << "Nepoznata opcija, molimo odaberite ponovo.\n";
                break;
            }
        }
    }

    return 0;
}
