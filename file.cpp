#include "file.h"
#include "memtrace.h"
#include <iostream>
#include <fstream>
#include "hibakezeles.hpp"

KoltsegLista* File::read() {
    std::ifstream file(fileName.getC());
    if (!file.is_open()) throw FileHiba("Hibás fájl");
    
    KoltsegLista* lista = nullptr;
    try {
        lista = new KoltsegLista();
    } catch (const std::bad_alloc&) {
        file.close();
        throw MemoriaHiba("Nem sikerült memóriát foglalni a KoltsegLista számára");
    }

    String s;
    int error = 0;
    file >> s;
    
    while (s != "") {
        Vektor<String> tmp = s.split(';');
        if (tmp.length() == 4) {
            try {
                double ertek = tmp[2].toUnsignedDouble();
                int id = tmp[0].toInt();
                Koltseg k = Koltseg(Datum(tmp[1]), tmp[3], ertek, id);
                lista->push_back(k);
            } catch (std::invalid_argument& kivetel) {
                std::cout << "sor: " << s << std::endl << "[HIBA] " << kivetel.what() << "\n\n";
                error++;
            }
        } else {
            std::cout << "sor: " << s << std::endl << "[HIBA] " << "Várt adatok száma: 4" << std::endl << "Érkezett adatok száma: " << tmp.length() << "\n\n";
            error++;
        }
        tmp.clear();
        file >> s;
    }

    std::cout << "A beolvasás során kapott hibák száma:" << error << std::endl;
    std::cout << "Beolvasott:" << std::endl;
    lista->kiir("");

    if (error) {
        String valasz;
        std::cout << "Szeretné a fájl megjavítását? I = igen, bármilyen más karakter = nem: ";
        std::cin >> valasz;
        while (valasz == "") {
            std::cin >> valasz;
        }
        if (valasz == "I") {
            std::cout << "A fájl megjavításra került" << std::endl;
            write(lista);
        }
    }

    file.close();
    return lista;
}

void File::write(KoltsegLista* lista) {
    std::ofstream file(fileName.getC());
    if (!file.is_open()) throw FileHiba("Nem sikerült megnyitni a fájlt írásra");

    for (size_t i = 0; i < lista->length(); i++) {
        file << lista->operator[](i).getId() << ";" 
             << lista->operator[](i).getIdo() << ";" 
             << std::fixed << (lista->operator[](i).getOsszeg()) << ";" 
             << lista->operator[](i).getLeiras() << std::endl;
    }

    file.close();
}