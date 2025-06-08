#include "datum.h"
#include <stdexcept>
#include "hibakezeles.hpp"
#include <iomanip>


bool Datum::szokoev() const{
    return (ev % 4 == 0 && ev % 100 != 0) || (ev % 400 == 0);
}

bool Datum::valide() const{
        if (ev < 1 || honap < 1 || honap > 12 || nap < 1) return false;
        int napokSzama[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if (honap == 2 && szokoev()) return nap <= 29;
        return nap <= napokSzama[honap - 1];
}

Datum::Datum(String d){
    String l = "";
    Szektorok szektorok = EV;
    bool rossz = false;
    ev = -1; honap = 1; nap = 1;
    Vektor<String> elemek = d.split('-');
    if (elemek.length() == 3){
    for (size_t i = 0; i < elemek.length(); i++){
        try{
            if (szektorok == EV) {if (elemek[i].length() == 4) ev = elemek[i].toInt(); else rossz = true; szektorok = HONAP; }
            else if (szektorok == HONAP) {if (elemek[i].length() == 2)honap = elemek[i].toInt(); else rossz = true; szektorok = NAP; }
            else if (szektorok == NAP) {if (elemek[i].length() == 2) nap = elemek[i].toInt(); else rossz = true; szektorok = VEGE; }
            l = "";
        }catch(HibasSzam& hiba){
            throw HibasDatum("A dátum formátuma hibás. A helyes dátum: YYYY-MM-DD"); //std::invalid_argument("Hibás formátum: dátum");
        }
    }
    if (szektorok!=VEGE) nap = l.toInt();
    }
    if (((honap <= 0 || nap <= 0 || szektorok != VEGE) && d != "") || rossz) throw HibasDatum("A dátum formátuma hibás. A helyes dátum: YYYY-MM-DD"); //std::invalid_argument("Hibás formátum: dátum");
    if (!valide() && ev != -1){
        throw HibasDatum("Nem létező dátum");
    }
}

bool Datum::operator>( const Datum& d) const{
    if (d.ev < ev) return true;
    else if (d.ev == ev) {
        if (d.honap < honap) return true;
        else if(d.honap == honap){
            if (d.nap < nap) return true;
        }
    }
    return false;
}


bool Datum::operator>=(const Datum& d) const{
    if (d.ev < ev) return true;
    else if (d.ev == ev) {
        if (d.honap < honap) return true;
        else if(d.honap == honap){
            if (d.nap < nap) return true;
        }
    }
    return (*this) == d;
}

bool Datum::operator<( const Datum& d) const{
    if (d.ev > ev) return true;
    else if (d.ev == ev) {
        if (d.honap > honap) return true;
        else if(d.honap == honap){
            if (d.nap > nap) return true;
        }
    }
    return false;
}

bool Datum::operator<=( const Datum& d) const{
    if (d.ev > ev) return true;
    else if (d.ev == ev) {
        if (d.honap > honap) return true;
        else if(d.honap == honap){
            if (d.nap > nap) return true;
        }
    }
    return (*this) == d;
}

bool Datum::operator==( const Datum& d) const{
    return d.ev == ev && d.honap == honap && d.nap == nap;
}

std::ostream& operator<<(std::ostream& os, Datum& d){
    os << std::setfill('0') << std::setw(4) << d.getEv() << "-" << (d.getHonap() < 10 ? "0" : "") << d.getHonap() << "-" << (d.getNap() < 10 ? "0" : "") << d.getNap();
    return os;
}