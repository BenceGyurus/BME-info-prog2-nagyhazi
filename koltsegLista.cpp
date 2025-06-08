#include "koltsegLista.h"
#include "string.h"
#include <stdexcept>

void KoltsegLista::push_back(Datum d, double osszeg, String leiras){
    int kovId = 0;
    for (size_t i = 0; i < lista.length(); i++){
        if (lista[i].getId() > kovId) kovId = lista[i].getId();
    }
    kovId++;
    if (d.getEv() != -1 && leiras != "" && osszeg != -1){lista.push_back(Koltseg(d, leiras, osszeg, kovId));}
    else throw HibasBemenet("Hiányos vagy hibás adatok");
}

bool KoltsegLista::find(const int id){
    for (size_t i = 0; i < lista.length(); i++){
        if (lista[i].getId() == id) return true;
    }
    return false;
}

void KoltsegLista::push_back(Koltseg k){
    if (!find(k.getId()) && k.getId() > 0) lista.push_back(k);
    else throw HibasBemenet("Ezzel az azonosítóval már van elem");
}

void KoltsegLista::KiirOsszeg(Datum d1, Datum d2, std::ostream& os){
    double osszeg = 0;
    for (size_t i = 0; i < lista.length(); i++){
        if ((lista[i].getIdo() >= d1 && lista[i].getIdo() <= d2 ) || d1.getEv() == -1) osszeg += lista[i].getOsszeg();
    }
    os << "Összeg: " << osszeg << std::endl;
}

void KoltsegLista::kiir(String szures, std::ostream& os){
    bool volt = false;
    bool elso = true;
    for (size_t i = 0; i < lista.length() ; i++){
        if (lista[i].getLeiras().includes(szures)) {
            if (elso){
                os << "ID\tDÁTUM\t\tÉRTÉK\tLEÍRÁS\n";
            } 
            os << lista[i] << std::endl; 
            volt = true;
            elso = false;
        }
    }
    if (!volt) os << "Nincs a keresésnek megfelelő adat";
    os << "\n\n";
}

bool KoltsegLista::torles(int id){
    bool torolt = false;
    for (size_t i = 0; i < lista.length(); i++){
        if (lista[i].getId() == id){
            lista.torol(&lista[i]);
            torolt = true;
        }
    }
    return torolt;
}

void KoltsegLista::szerkeszt(int id, Datum d, double osszeg, String leiras){
    for (size_t i = 0; i < lista.length(); i++){
        if (lista[i].getId() == id){
            if (leiras != "") lista[i].setLeiras(leiras);
            if (osszeg >= 0) lista[i].setOsszeg(osszeg);
            if (d.getEv() != -1) lista[i].setIdo(d);
        }
    }
}