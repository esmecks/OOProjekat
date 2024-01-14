#ifndef IMENIK_TIPKONTAKTA
#define IMENIK_TIPKONTAKTA
#include <iostream>

enum class TipKontakta{
    Poslovni,
    Licni,
    Ostalo
};

inline std::ostream& operator<<(std::ostream& os, TipKontakta tip) {
    switch (tip) {
        case TipKontakta::Poslovni:
            os << "Poslovni";
            break;
        case TipKontakta::Licni:
            os << "Licni";
            break;
        case TipKontakta::Ostalo:
            os << "Ostalo";
            break;
        default:
            os << "Nepoznat";
            break;
    }
    return os;
}

#endif

