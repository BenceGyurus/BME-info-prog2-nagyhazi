#include "datum.h"
#include "string.h"
#include "memtrace.h"

#ifndef KOLTSEG_H
#define KOLTSEG_H


/**
 * Költség osztály
 */
class Koltseg{
    Datum ido;      // A költség dátuma
    String leiras;  // A költéség leírása
    double osszeg;  // A Költség összege
    int id;         // A költség id-ja
    public:
    /**
     * alapértelmezett konstruktor
     */
    Koltseg() : ido(), leiras(""), osszeg(0), id(0) {}
    /**
     * @param d költség dátuma
     * @param l költség leírása
     * @param o költség összeg
     * @param id költség azonosítója
     */
    Koltseg(Datum d, String l, double o, int id){
        if (id < 0){
            throw HibasBemenet("Negatív az azonosító");
        }else{
            this->id = id;
        }
        if (d.getEv() >= 0){
            ido = d;
        }else{
            throw HibasDatum("Hibás dátum");
        }
        if (l == ""){
            throw HibasBemenet("Üres leírás");
        }else{
            leiras = l;
        }
        if (o >= 0){
            osszeg = o;
        }else{
            throw HibasBemenet("Negatív összeg");
        }
    }
    /**
     * @return visszadja a költség dátumát
     */
    Datum& getIdo(){ return ido; }
    /**
     * @return visszaadja a költség összegét
     */
    double getOsszeg() const { return osszeg; }
    /**
     * @return Visszaadja a költség leírását
     */
    const String& getLeiras() const { return leiras; }
    /**
     * @return visszaadja a költség azonosítóját
     */
    int getId() { return id; }
    /**
     * beállítja a paraméterként kapott Datum-ot a költség idejének
     * @param d a beállítani kívánt Datum
     */
    void setIdo(const Datum& d);
    /**
     * beállítja a paraméterként kapott doublet a költség összegénekk
     * @param o a beállítani kívánt összeg
     */
    void setOsszeg(double o);
    /**
     * beállítja a paraméterként kapott Stringet a költség leírásának
     * @param d a beállítani kívánt Datum
     */
    void setLeiras(String& leiras);

};

/**
     * beállítja a paraméterként kapott Datum-ot a költség idejének
     * @param d a beállítani kívánt Datum
*/
std::ostream& operator<<(std::ostream& os, Koltseg& k);

#endif
