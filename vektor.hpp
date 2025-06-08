#include <iostream>
#include "hibakezeles.hpp"

#ifndef VEKTOR_H
#define VEKTOR_H


/**
 * Vektor osztály
 */
template <typename T>
class Vektor{
    /**
    * A láncolt lista struktúrája
    */
    struct Lista{
        T adat;
        Lista* kov;
    };
    Lista* lancolt;
    size_t size;
    public:
    /*
    * Vektor alapértelezett konstruktora, 0-ra állítja a hoszzát
    */
    Vektor():size(0){
        lancolt = nullptr;
    }
    Vektor(T& adat){
        lancolt = nullptr;
        Lista* tmp = nullptr;
        try{
            tmp = new Lista;
        }catch(std::bad_alloc){
            throw MemoriaHiba("Nem sikerült memóriát foglalni"); // hibakezelés
        }
        tmp->adat = adat;
        tmp->kov = lancolt;
        lancolt = tmp;
        size = 1;
    }
    /**
     * A vektor copy konstruktora
     * @param v a másodlandó vektor
    */
    Vektor(const Vektor& v){
        Lista* tmp;
        lancolt = nullptr;
        size = 0;
        for (Lista* i = v.lancolt; i != nullptr; i = i->kov){
            tmp = nullptr;
            try{
                tmp = new Lista;
            }catch(std::bad_alloc){
                throw MemoriaHiba("Nem sikerült memóriát foglalni"); // new hibakezelés
            }
            tmp->adat = T(i->adat);
            tmp->kov = lancolt;
            lancolt = tmp;
            size++;
        }
    }
    /**
    * @return a láncolt lista mérete
    */
    size_t length() const{
        return size;
    }

    /**
     * Hozzáad a láncolt listához egy elemet
     * @param adat a hozzáadandó adat
     */
    void push_back(T adat){
        Lista* tmp = nullptr;
        try{
            tmp = new Lista;   
        }catch(std::bad_alloc){
            throw MemoriaHiba("Nem sikerült memóriát foglalni"); // new hibakezelés
        }
        tmp->adat = adat;
        tmp->kov = lancolt;
        lancolt = tmp;
        size++;
    }

    /**
     * indexelő operátor
     * @return paraméterként kapott elem
     */
    const T& operator[](size_t index) const{
        size_t szamlalo = 0;
        if (index > size || index < 0) throw std::out_of_range("Nincs ilyen elem");
        for (Lista* i = lancolt; i!=nullptr; i = i->kov){
            if (szamlalo == size-index) return i->adat;
            szamlalo++;
        }
        throw std::out_of_range("Nincs ilyen elem");
    }

    T& operator[](size_t index){
    size_t szamlalo = 0;
    if (index >= size || index < 0) throw std::out_of_range("Nincs ilyen elem");
    for (Lista* i = lancolt; i!=nullptr; i = i->kov){
        if (szamlalo == (size-1)-index) return i->adat;
        szamlalo++;
    }
    throw std::out_of_range("Nincs ilyen elem");
    }

    /**
     * kiüríti a láncolt listát és felszabadítja az elemeit
     */
    void clear(){
        Lista* elozo = lancolt;
        while (elozo != nullptr){
            Lista* tmp = elozo->kov;
            delete elozo;
            elozo = tmp;
        }
        lancolt = nullptr;
        size = 0;
    }

    /**
     * érétkadó operátor
     * @param elem az elem referenciája amit szeretnénk értékül adni
     * @return visszaadja magát módosítva
     */
    Vektor<T>& operator=(Vektor<T>& ujLista){
        clear();
        for (Lista* i = ujLista; i != nullptr; i=i->kov){
            push_back(i);
        }
        return (*this);
    }

    /**
     * Tori a paraméterként megadott elemet
     * @param torlendo a törlendő elem memóriacíme
     */
    void torol(T* torlendo){
        Lista* elozo = nullptr;
        Lista* i = lancolt;
        for (; i != nullptr; i = i->kov){
            if (&(i->adat) == torlendo) {
                if (elozo == nullptr) lancolt = i->kov;
                else{
                    elozo->kov = i->kov;
                }
                break;
            }
            elozo = i;
        }
        delete i;
        size--;
    }

    /**
     * destruktor
     */
    virtual ~Vektor(){
       clear();
    }

};

#endif