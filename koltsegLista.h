#include "vektor.hpp"
#include "koltseg.h"
#include "memtrace.h"


#ifndef KOLTSEGLISTA_H
#define KOLTSEGLISTA_H

class KoltsegLista{

    Vektor<Koltseg> lista;     // Lista a költségekkel

    public:
    /**
     * visszaadja, hogy az adott id-val van-e elem a listában
     * @param id egy size_t típusú id
     * @return logikai érték, benn van-e az elem ezzel az id-val
     */
    bool find(const int id);
    /**
     * Alapértelmezett konstruktor
     */
    KoltsegLista(){};
    /**
     * copy konstruktor
     * @param k egy költség referenciája
     */
    KoltsegLista(Koltseg& k){
        lista.push_back(k);
    };
    /**
     * hozzáadja a listához az adott elemet, autómatikusan ad id-t
     * @param d egy érvényes Datum
     * @param osszeg a költség összege, double típusként
     * @param leiras egy érvényes (nem üres) String
     */
    void push_back(Datum d, double osszeg, String leiras);
    /**
     * hozzáadja a listához az adott elemet, a megadott id-t ellenőrzi, hogy benn van-e már a listában, ha igen akkor hibát dob
     * @param koltseg egy költség amit hozzá szeretnénk adni a listához
     */
    void push_back(Koltseg);
    /**
     * kiírja, hogy a két megadott dátum között mennyi a listában szereplő költségek összege, ha nincs dátum megadni akkor az összes költséget írja ki
     * @param d1 a kezdő dátum, kisebbnek kell lennie, msize_t d2-nek (opcionális)
     * @param d2 a befejező dátum, mind a két dátum esetében zárt size_tervallumra nézi, tehát még a két datum szerepel benne (opcionális)
     */
    void KiirOsszeg(Datum d1, Datum d2, std::ostream& os = std::cout);
    /**
     * Kiírja az adott szűrési feltétel mellet a listában szereplő kölségeket, a szűrés a leírásra vonatkozik
     * @param szures egy String amit megnéz, hogy szerepel-e a listában szereplő elemek lírásában, amelyiken a feltétel teljesül azt kiírja, ha nincs feltétel akkor nem kötelező megadni
     */
    void kiir(String szures = String(), std::ostream& os = std::cout);
    /**
     * törli a megadott id-val rendekező elemet
     * @param id egy size_t típusú id
     */
    bool torles(int id);
    /**
     * felülírja a paraméterként megadott adatokkal a megadott id-val rendekező elemet, csak azokat írja felül ami érvényes, tehát nem üres String, Datum, illetve, osszeg > 0
     * @param id egy érvényes size_t típusú azonosító (kötelező)
     * @param d egy érvényes Datum (opcinális)
     * @param osszeg 0-nál nagyobb double (opcionális)
     * @param leiras nem üres String (opcionális)
     */
    void szerkeszt(int id, Datum d = Datum(), double osszeg = -1, String leiras = String());
    /**
     * Visszaadja a költséglista hosszát
     * @return a költséglista hossza
     */
    size_t length() const{
        return lista.length();
    }
    
    /**
     * indexelő operátor
     * @param index az elem indexe amit szeretnénk megkapni
     * @return a paraméterként megkapott indexnek megfelelő elem a listában - nem változtatható a megkapott elem értéke
     */
    const Koltseg& operator[](size_t index) const{
        return lista[index];
    }

    /**
     * indexelő operátor
     * @param index az elem indexe amit szeretnénk megkapni
     * @return a paraméterként megkapott indexnek megfelelő elem a listában - változtatható a megkapott elem értéke
     */
    Koltseg& operator[](size_t index){
        return lista[index];
    }
};

#endif