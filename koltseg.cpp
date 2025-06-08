#include "koltseg.h"
#include "memtrace.h"
#include <iomanip>

void Koltseg::setIdo(const Datum& d){
    ido = d;
}

void Koltseg::setOsszeg(double o){
    osszeg = o;
}

void Koltseg::setLeiras(String& l){
    leiras = l;
}

std::ostream& operator<<(std::ostream& os, Koltseg& k){
    os << k.getId() <<  '\t' << k.getIdo() << "\t" << k.getOsszeg() << "\t" << k.getLeiras();
    return os;
}