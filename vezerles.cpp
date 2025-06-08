#include "vezerles.h"
#include "datum.h"
#include <iostream>

Vezerles::Vezerles(const String& filename, std::ostream& os, std::istream& in) : os(os), in(in), f(filename), allapot(URES) {
    lista = f.read();
}

Vezerles::~Vezerles() {
    f.write(lista);
    delete lista;
}

void Vezerles::menuKiir(std::ostream& os) const {
    os << "************************************\n"
              "*         KÖLTSÉG  LISTÁZÓ         *\n"
              "************************************\n"
              "* 1. Költség hozzáadása            *\n"
              "* 2. Költségek listázása           *\n"
              "* 3. Összegzés                     *\n"
              "* 4. Szerkesztés                   *\n"
              "* 5. Törlés                        *\n"
              "* 6. Kilépés                       *\n"
              "************************************\n"
              "\n"
              "\nVálasszon egy menüpontot (1-6): ";
}

void Vezerles::run() {
    String beolvasott; 
    try{
        beolvasott = "0";
    }catch(MemoriaHiba& hiba){
        throw hiba;
    }
    while (beolvasott != "6"){
        menuKiir(os);
        if (!(in >> beolvasott)) {
            break;
        }
        if (allapot == URES) {
            if (beolvasott == "1") allapot = UJ;
            else if (beolvasott == "2") allapot = LISTAZ;
            else if (beolvasott == "3") allapot = OSSZEGEZ;
            else if (beolvasott == "4") allapot = SZERKESZT;
            else if (beolvasott == "5") allapot = TOROL;
            else if (beolvasott == "6") break;
            else {
                os << "Kérlek a felsorolt műveletekből válassz" << std::endl;
            }
        }
        try{
            switch (allapot) {
                case UJ: handleUj(); break;
                case LISTAZ: handleListaz(); break;
                case OSSZEGEZ: handleOsszegez(); break;
                case SZERKESZT: handleSzerkeszt(); break;
                case TOROL: handleTorol(); break;
                default: break;
            }
        }catch(std::runtime_error& error){
            throw error;
        }catch(...){
            throw std::runtime_error("Váratlan hiba történt");
        }
    }
}

void Vezerles::handleUj() {
    try {
        String s2, s3, s4;
        os << "A költség dátuma: ";
        in >> s2;
        Datum d(s2);
        os << "A költség összege: ";
        in >> s3;
        double ertek = s3 != "" ? s3.toUnsignedDouble() : -1;
        os << "A költség leírása: ";
        in >> s4;
        lista->push_back(d, ertek, s4);
    } catch(std::invalid_argument& kivetel) {
        os << "[HIBA] " << kivetel.what() << std::endl;
    }catch(MemoriaHiba& kivetel){
        throw kivetel;
    }catch(...){
        throw std::runtime_error("Váratlan hiba történt a program futása közben");
    }
    allapot = URES;
}

void Vezerles::handleListaz() {
    try{
        String szures;
        os << "Add meg, hogy mire szeretnél szűrni (Ha nem szeretnél akkor csak hagy üresen) : ";
        in >> szures;
        lista->kiir(szures, os);
    }catch(std::invalid_argument& kivetel) {
        os << "[HIBA] " << kivetel.what() << std::endl;
    }catch(MemoriaHiba& kivetel){
        throw kivetel;
    }catch(...){
        throw std::runtime_error("Váratlan hiba történt a program futása közben");
    }
    allapot = URES;
}

void Vezerles::handleOsszegez() {
    String tolStringBen, igStringBen;
    os << "Dátum ahonnan szeretnéd: (Ha az összeset szeretnéd akkor hagyd üresen)";
    in >> tolStringBen;
    try {
        Datum tolDatum = Datum(tolStringBen);
        if (tolStringBen != "") {
            os << "Dátum ameddig szeretnéd: ";
            in >> igStringBen;
        }
        Datum igDatum = Datum(igStringBen);
        if (igDatum >= tolDatum) {
            lista->KiirOsszeg(tolDatum, igDatum, os);
        } else {
            os << "[HIBA] Az első dátumnak kisebbnek kell lennie!" << std::endl;
        }
    }catch(std::invalid_argument& kivetel) {
        os << "[HIBA] " << kivetel.what() << std::endl;
    }catch(MemoriaHiba& kivetel){
        throw kivetel;
    }catch(...){
        throw std::runtime_error("Váratlan hiba történt a program futása közben");
    }
    allapot = URES;
}

void Vezerles::handleSzerkeszt() {
    String azon, datum, penz, szoveg;
    os << "A szerkeszteni kívánt elem azonoítója: ";
    in >> azon;
    try {
        int id = azon.toInt();
        if (lista->find(id)) {
            os << "Dátum szerkesztése (Ha nem szeretnéd szerkeszteni, hagyd üresen): ";
            in >> datum;
            Datum d(datum);
            os << "Összeg szerkesztése (Ha nem szeretnéd szerkeszteni, hagyd üresen): ";
            in >> penz;
            double ertek = penz != "" ? penz.toUnsignedDouble() : -1;
            os << "Leírás szerkesztése (Ha nem szeretnéd szerkeszteni, hagyd üresen): ";
            in >> szoveg;
            lista->szerkeszt(id, d, ertek, szoveg);
            if (datum != "" || penz != "" || szoveg != "") os << "Sikeres mentés!" << std::endl;
            else os << "Nem változott!" << std::endl;
        } else {
            os << "[HIBA] Nincs elem ilyen azonosítóval!" << std::endl;
        }
    }catch(std::invalid_argument& kivetel) {
        os << "[HIBA] " << kivetel.what() << std::endl;
    }catch(MemoriaHiba& kivetel){
        throw kivetel;
    }catch(...){
        throw std::runtime_error("Váratlan hiba történt a program futása közben");
    }
    allapot = URES;
}

void Vezerles::handleTorol() {
    String s1;
    os << "A törölni kívánt elem azonoítója: ";
    in >> s1;
    try {
        int id = s1.toInt();
        if (lista->torles(id)){
            os << "Sikeres törlés!" << std::endl;
        }else{
            os << "Sikertelen  törlés, nem található a törölni kívánt elem" << std::endl;
        }
    }catch(std::invalid_argument& kivetel) {
        os << "[HIBA] " << kivetel.what() << std::endl;
    }catch(MemoriaHiba& kivetel){
        throw kivetel;
    }catch(...){
        throw std::runtime_error("Váratlan hiba történt a program futása közben");
    }
    allapot = URES;
}