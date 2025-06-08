#include "string.h"
#include "memtrace.h"

#ifndef DATUM_H
#define DATUM_H

/**
 * @class Datum
 * 
 * a dátumok kezelésére használható osztály
*/
class Datum{

    /**
    * Tagfüggvény segéd enum
    */
    enum Szektorok{
        EV,
        HONAP,
        NAP,
        VEGE
    };

    /**
     * Megadja, hogy az oszály ev változójának értéke szököév-e
     * @return true - ha az adott év szökőév, false - ha az adott év szökőév-e
     */
    bool szokoev() const;

    /**
     * Megadja, hogy az adott dátum valid-e, tehát nem-e negítvak az értékek, van-e annyi hónap az évben és ennyi nap az adott hónapban
     * @return true - ha valid, false - ha invalid
     */
    bool valide() const;

    int ev;
    int honap;
    int nap;
    public:
    /**
     * default konstruktor, alapértelmezetten az évet -1-re állítja
     */
    Datum(): ev(-1), honap(1), nap(1){}
    /**
    * @param ev - az év, nincs alapértelmezett értéke
    * @param honap - a hónap, alapértelmezetten 1
    * @param nap - a nap, alapértelmezetten 1
    */
    Datum(int ev, int honap = 1, int nap = 1): ev(ev), honap(honap), nap(nap){
        if (!valide()){
            throw HibasDatum("Nem létező dátum");
        }
    }
    /**
     * String típusból csinál Datum típust
     * @param d YYYY-MM-DD formátumú String, ellenkező esetben hibát dob vissza
     */
    Datum(String d);
    /**
     * Két dátum összehasonlítására d1 > d2 formában
     * @param d amivel össze akarjuk hasonlítani a Datumot
     */
    bool operator>( const Datum& d) const;
    /**
     * Két dátum összehasonlítására d1 >= d2 formában
     * @param d amivel össze akarjuk hasonlítani a Datumot
     */
    bool operator>=(const Datum& d) const;
    /**
     * Két dátum összehasonlítására d1 < d2 formában
     * @param d amivel össze akarjuk hasonlítani a Datumot
     */
    bool operator<( const Datum& d) const;
    /**
     * Két dátum összehasonlítására d1 <= d2 formában
     * @param d amivel össze akarjuk hasonlítani a Datumot
     */
    bool  operator<=( const Datum& d) const;
    /**
     * Két dátum összehasonlítására d1 == d2 formában
     * @param d - amivel össze akarjuk hasonlítani a Datumot
     */
    bool operator==( const Datum& d) const;
    /**
     * Visszaadja az évet
     * @return év
     */
    int getEv() const {return ev;}
    /**
     * Visszaadja a hónapot
     * @return int
     */
    int getHonap()const {return honap;}
    /**
     * Visszaadja a napot
     * @return int
     */
    int getNap()const {return nap;}
};

/**
 * Kiírja a dátumot a paraméterként kapottt kimenetre
 * @param os - adatfolyam amire kiírja a dátumot
 * @param d - kiírandó dátum
 * @return ostream&
 */
std::ostream& operator<<(std::ostream& os, Datum& d);

#endif