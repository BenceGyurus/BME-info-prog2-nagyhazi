#ifndef FILE_H
#define FILE_H


#include <iostream>
#include <fstream>
#include "string.h"
#include "datum.h"
#include "koltseg.h"
#include "koltsegLista.h"
#include <cmath>


/**
 * @class File
 * 
 * Fájl megnyitására és írására használható osztály
 */
class File{

    String fileName;
    public:
    /**
     * megadja a fájlnevet
     */
    File(String fileName): fileName(fileName){}
    /**
     * megnyitja a fájlt, kiolvassa és Koltseglista* ként visszatér vele
     * @return KoltsegLista* típusu pointerrel tér vissza, amiben már benne vannak a fájlból kiolvasott adatok
     */
    KoltsegLista* read();
    /**
     * kiírja a fájlba a paraméterként kapott listát
     * @param lista KoltsegLista* típusú pointer amit szeretnénk kiírni a fájlba
     */
    void write(KoltsegLista* lista);

};

#endif
