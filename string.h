#include "memtrace.h"
#include <iostream>
#include "vektor.hpp"
#ifndef STRING_H
#define STRING_H

class String {
    char *pData;
    size_t len;
public:
    /**
     * Alapértelmezett konstruktor
     */
    String() :len(0) {
        try{
        pData = new char[1];
        pData[0] = '\0';
        }catch(std::bad_alloc){
            throw MemoriaHiba("Nem sikerült memóriát foglalni."); 
        }
    }
    /**
     * @param c karakterből String
     */
    String(const char c);


    /**
     * @param c const char*-ból string
     */
    String(const char* c);

    /**
     * copy konstruktor
     * @param s a másoladnó String
     */
    String(const String& s);

    /**
     * Értékadó operátor const String&
     * @param s a másolandó String
     */
    String& operator=(const String& s);
    /**
     * Értékadó operátor const char* s
     * @param s átmásolja a const char*-ot a Stringnek
     */
    String& operator=(const char* s);

    /**
     * indexelő operátor
     * @param i az elem indexe
     * @return visszaadja paramtéerként kapott indexű elemet
     */
    char& operator[](const size_t i) const;

    char& operator[](const size_t i);
    /**
     * @return a string hossza
     */
    size_t length() const { return len; }

    /**
     * megadja, hogy egy elemet tartalmaz-e részben vagy teljesen a String, csak pontos egyezést néz a kisebb részhalmazokra
     * @param str ellenőrizendő elem
     * @return logikai érték, igaz, ha az ellenőrizendő elem benne van a Stringbe, hamis ha nincs
     */
    bool includes(const String& str) const;

    /**
     * nem egyenlő operátor, jobb és bal operandusa is String
     * @param str a jobb oldali operandus
     * @return logikai érték, igaz, ha nem egyenlő, hamis ha egyenlő
     */
    bool operator!=(const String& str) const;
    /**
     * nem egyenlő operátor, bal operandusa String, a jobb operandusa const char*
     * @param str a jobb oldali operandus
     * @return logikai érték, igaz, ha nem egyenlő, hamis ha egyenlő
     */
    bool operator!=(const char* str) const;


    /**
     * egyenlő operátor, jobb és bal operandusa is String
     * @param str a jobb oldali operandus
     * @return logikai érték, igaz, ha egyenlő, hamis ha nem egyenlő
     */
    bool operator==(const String& str) const;
    
    /**
     * egyenlő operátor, bal operandusa String, a jobb operandusa const char*
     * @param str a jobb oldali operandus
     * @return logikai érték, igaz, ha egyenlő, hamis ha nem egyenlő
     */
    bool operator==(const char* str) const;

    /**
     * összeadás operátor const char*-al
     * @param c a jobb oldali operandus
     * @return egy új String, ami az paraméterként kapott const char* és az eredeti String összege
     */
    String operator+(const char c) const;
    /**
     * összeadás operátor const String-el
     * @param s a jobb oldali operandus
     * @return egy új String, ami az paraméterként kapott String és az eredeti String összege
     */
    String operator+(const String& s) const;

    /**
     * += operátor, const String-el
     * @return visszaadja az összeadott String-et
     */
    String& operator+=(const String& s);
    /**
     * += operátor, const const char*-al
     * @return visszaadja az összeadott String-et
     */
    String& operator+=(const char* s);
    /**
     * += operátor, const char-al
     * @return visszaadja az összeadott String-et
     */
    String& operator+=(const char s);

    /**
     * visszadja integerbe átváltva ha String értéke valamilyen szám, csak prozitív előjelű számokra működik, csak számok lehetnek a Stringben
     * @return az átváltott szám
     */
    int toInt() const;

    /**
     * visszadja doubleben átváltva ha String értéke valamilyen szám, csak prozitív előjelű számokra működik, csak számok és egy darab . karakter lehet az stringben
     * @return az átváltott lebegőpontos szám
     */
    double toUnsignedDouble() const;

    /**
     * Feladarabolja a String-et egy paraméterként megadott karakterenként
     * @param c ami mentén szeretnénk feladabolni a Stringet
     * @return Vektor<String> - ként fogja visszaadni a feladarabolt stringeket
     */
    Vektor<String> split(const char c) const;


    /**
     * const char* ként adja vissza a String értékét
     * @return const char* ként a string
     */
    const char* getC() const{
        return pData;
    }
    
    /**
     * Destruktor
     */
    ~String();

};

/**
 * Kiírja a Stringet a paraméterként kapott streambe
 * @param os - adatfolyam amire kiírja a karaktersorozatot
 * @param d - kiírandó String
 * @return ostream&
 */
std::ostream& operator<<(std::ostream&, const String& s);


/**
 * Beolvassa a Stringet a paraméterként kapott streamből
 * @param os - adatfolyam amire kiírja a karaktersorozatot
 * @param d - amibe szeretnénk beolvasni String-et
 * @return ostream&
 */
std::istream& operator>>(std::istream& is, String& rhs);







#endif
