#ifndef VEVERLES_H
#define VEVERLES_H

#include "file.h"
#include "koltsegLista.h"
#include "string.h"
#include <iostream>

class Vezerles {
    std::ostream& os;           // erre a streamre ír ki az osztály
    std::istream& in;           // erről a streamtől olvas be az osztály
    /**
     * A vezérlés állapotai
     */
    enum Allapot {
        UJ,
        LISTAZ,
        OSSZEGEZ,
        SZERKESZT,
        TOROL,
        URES
    };
    /**
     * Menu kiírására szolgáló függvény
     * @param os a stream amire kiíra a menüt
     */
    void menuKiir(std::ostream& os) const;
    /**
     * Az új költség hozzáadásakor hívja meg a menü, ez kiírja és be is olvassa az adatokat, kezeli a hibákat
     */
    void handleUj();
    /**
     * A költségeket listázza ki és bekéri az ehhez szükséges adatokat
     */
    void handleListaz();
    /**
     * Az összegző menüpontot kezeli, ez hívódik meg összegzéskor ami bekéri a megfelelő adatokat
     */
    void handleOsszegez();
    /**
     * Minden szerkesztéshez szükséges folyamatot kezel
     */
    void handleSzerkeszt();
    /**
     * A törléshez szükséges adatok bekérése és a törlés elvégzése
     */
    void handleTorol();

    File f;                     // a fájl ahonnan az adatokat beolvassa
    KoltsegLista* lista;        // a költséglista
    Allapot allapot;            // a jelenlegi állapota a vezérlésnek
    
    public:
    /**
     * Vezérlés kontruktora
     * @param filename annak a fájlnak a neve ahonnak az adatokat olvassa be
     * @param os ezt a streamet használja a kiírásra
     * @param in ezt a streamet használja a beolvasásra
     */
    Vezerles(const String& filename, std::ostream& os = std::cout, std::istream& in = std::cin);
    /**
     * Destruktor
     */
    ~Vezerles();
    /**
     * A menü futtatása, elindítja a fő ciklust
     */
    void run();
};

#endif // VEVERLES_H