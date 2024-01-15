#include "Imenik.h"
#include<iostream>
#include<vector>



int main(){

    Imenik imenik;

    int izbor = 0;
    while(izbor != 11){
        imenik.prikaziMeni();
        std::cin >> izbor;

        switch(izbor){
            //unos
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

                imenik.dodajKontaktUTextDatoteku(noviKontakt);

                std::cout << "Kontakt je uspjesno dodan.\n\n";
                break;
            }
            //brisanje
            case 2: {
                std::string brojTelefona,ime,prezime;

                std::cout<<"Unesite ime:";
                std::cin>>ime;
                std::cout<<"Unesite prezime:";
                std::cin>>prezime;
                imenik.obrisiKontaktIzDatoteke(ime,prezime);
                //std::cout << "Kontakt je uspjesno obrisan.\n\n";
                break;
            }
            //pronalazak kontakta
            case 3: {
                std::string brojTelefona;
                std::cout << "Unesite broj telefona za pretragu kontakta: ";
                std::cin >> brojTelefona;

                imenik.ucitajIzDatoteke("imenik.txt");
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
            //ispis svih
            case 4: {
                imenik.ispisSvihKontakata("imenik.txt");
                break;
            }

            //uredjivanje kontakta
            case 5: {

                Imenik imenik;

                // Unos informacija od korisnika
                std::string staroIme, staroPrezime;
                std::cout << "Unesite ime kontakta koje zelite urediti: ";
                std::cin >> staroIme;

                std::cout << "Unesite prezime kontakta koje zelite urediti: ";
                std::cin >> staroPrezime;

                // Unos novih podataka od korisnika
                std::string novoIme, novoPrezime, noviBroj, novaAdresa;
                std::cout << "Unesite novo ime: ";
                std::cin >> novoIme;

                std::cout << "Unesite novo prezime: ";
                std::cin >> novoPrezime;

                std::cout << "Unesite novi broj telefona: ";
                std::cin >> noviBroj;

                std::cout << "Unesite novu adresu: ";
                std::cin.ignore();
                std::getline(std::cin, novaAdresa);


                std::cout << "Unesite novi tip kontakta (0 - Poslovni, 1 - Licni, 2 - Ostalo): ";
                int tipKontaktaInt;
                std::cin >> tipKontaktaInt;

                TipKontakta noviTipKontakta;
                switch (tipKontaktaInt) {
                    case 0:
                        noviTipKontakta = TipKontakta::Poslovni;
                        break;
                    case 1:
                        noviTipKontakta = TipKontakta::Licni;
                        break;
                    case 2:
                        noviTipKontakta = TipKontakta::Ostalo;
                        break;

                    default:
                        std::cerr << "Neispravan unos tipa kontakta. Postavljen je na Ostalo." << std::endl;
                        noviTipKontakta = TipKontakta::Ostalo;
                        break;
                }

                Kontakt noviPodaci(novoIme, novoPrezime, noviBroj, novaAdresa, noviTipKontakta);

                imenik.urediKontaktUDatoteci(staroIme, staroPrezime, noviPodaci);


              break;
            }
            //filtriranje
            case 6: {
                int tipUnos;
                std::cout << "Izaberite tip kontakta za filtriranje (0 - Poslovni, 1 - Licni, 2 - Ostalo): ";
                std::cin >> tipUnos;

                TipKontakta izabraniTip = static_cast<TipKontakta>(tipUnos);
                Imenik imenik;
                imenik.ucitajIzDatoteke("imenik.txt");
                imenik.filtrirajIspisiPoTipu(izabraniTip);


            break;
            }
            //sortiranje
            case 7: {
            std::string ulaznaDatoteka = "imenik.txt";
            std::string izlaznaDatoteka = "sortirani_imenik.txt";
            imenik.ucitajIzDatoteke(ulaznaDatoteka);
            imenik.sortirajKontakteIPisiUDatoteku(izlaznaDatoteka);
            std::cout << "Sortirani kontakti su spremljeni u datoteku: "<<izlaznaDatoteka<< std::endl;
            std::cout << "Sortirani kontakti su: "<<izlaznaDatoteka<< std::endl;
            imenik.ispisSvihKontakata("sortirani_imenik.txt");
            break;
            }
            //unos dodatnih
            case 8:{
            }
            //ispis dodatnih
            case 9:{
            }

            //izlaz
            case 10: {
                std::cout << "Izlaz iz programa.\n";
                break;
            }
            default: {
                std::cout << "Nepoznata opcija, molimo odaberite ponovo.\n";
                break;
            }
        }
    }

    Imenik imenik2;

     if (imenik == imenik2) {
        std::cout << "Imenici su jednaki." << std::endl;
    } else {
        std::cout << "Imenici nisu jednaki." << std::endl;
    }

    return 0;
}
