#include "string.h"
#include <cctype>
#include "memtrace.h"
#include <stdexcept>
#include <cstdlib>

/* Konstruktorok */

String::String(const char c) : len(1){
    try{
      pData = new char[len+1];
    }catch(std::bad_alloc){
      throw MemoriaHiba("Nem sikerült a stringnek memóriát foglalni");
    }
    pData[0] = c;
    pData[1] = '\0';
}

String::String(const char* c) : len(strlen(c)){
  try{
    pData = new char[len+1];
  }catch(std::bad_alloc){
      throw MemoriaHiba("Nem sikerült a stringnek memóriát foglalni");
  }
  strcpy(pData, c);
  pData[len] = '\0';
}


String::String(const String& s): len(s.len){
  try{
    pData = new char[len+1];
  }catch(std::bad_alloc){
      throw MemoriaHiba("Nem sikerült a stringnek memóriát foglalni");
  }
  strcpy(pData, s.pData);
  pData[len] = '\0';
}


/*
----------------------------
*/


bool String::operator!=(const String& str) const{
  if (str.len != len) return true;
  for (size_t i = 0; i < len; i++){
    if (pData[i] != str[i]) return true;
  }
  return false;
}


/*
----------------------------
*/


bool String::includes(const String& str) const{
    size_t matchIndex = 0;
    for (size_t i = 0; i < len; i++){
        if (str.length() > matchIndex && toupper(str[matchIndex]) == toupper(pData[i])) {matchIndex++;}
        else if (str[matchIndex] != pData[i]) matchIndex = 0;
        if (str.length() == matchIndex) return true;
    }
    return false;
}


/*
----------------------------
*/

String String::operator+(const char c) const {
    char* newStr;
    try{
        newStr = new char[len + 2];
    }catch(std::bad_alloc){
      throw MemoriaHiba("Nem sikerült a stringnek memóriát foglalni");
    }
    strcpy(newStr, pData);
    newStr[len] = c;
    newStr[len + 1] = '\0';
    String s = String(newStr);
    delete[] newStr;
    return s;
}

String String::operator+(const String& s) const{
    char* tmp;
    try{
      tmp = new char[s.len + len + 1];
    }catch(std::bad_alloc){
      throw MemoriaHiba("Nem sikerült a stringnek memóriát foglalni");
    }
    strcpy(tmp, pData);
    strcat(tmp, s.pData);
    tmp[s.len+len] = '\0';
    String eredmeny = String(tmp);
    delete[] tmp;
    return eredmeny;
}

/*
--------------------------
*/

String& String::operator=(const String& s){
    if (&s != this){
      len = s.len;
      delete[] pData;
      try{
        pData = new char[len+1];
      }catch(std::bad_alloc){
        throw MemoriaHiba("Nem sikerült a stringnek memóriát foglalni");
      }
      strcpy(pData, s.pData);
      pData[len] = '\0';
    }
    return (*this);
}

String& String::operator=(const char* s){
    len = strlen(s);
    delete[] pData;
    try{
      pData = new char[len+1];
    }catch(std::bad_alloc){
      throw MemoriaHiba("Nem sikerült a stringnek memóriát foglalni");
    }
    strcpy(pData, s);
    pData[len] = '\0';
    return (*this);
}

/*
--------------------------
*/


bool String::operator!=(const char* str) const{
  return strcmp(str, pData) != 0;
}

/*
--------------------------
*/


char& String::operator[](const size_t i) const{
  if (i < 0 || i > len) { throw std::out_of_range("Túlindexelés");}
  return pData[i];
}

char& String::operator[](const size_t i){
  if (i < 0 || i > len) { throw std::out_of_range("Túlindexelés");}
  return pData[i];
}

/*
--------------------------
*/


bool String::operator==(const String& str) const{
  return strcmp(str.pData, pData) == 0;
}


bool String::operator==(const char* str) const{
  return strcmp(str, pData) == 0;
}

/*
--------------------------
*/

int String::toInt() const{
  if (strlen(pData) < 1) throw HibasSzam("A megadott érték nem konvertálható számmá.");
  int hatvany = 1;
  int osszeg = 0;
    for (int i = len-1; i >= 0 ; i--){
      if ((pData[i] < 48 || pData[i] > 57) && pData[i] != '-') throw HibasSzam("A megadott érték nem konvertálható számmá.");
      if (pData[i] == '-' && i == 0){
        osszeg *= -1;
      }else if (pData[i] == '-' && i != 0){
        throw HibasSzam("A megadott érték nem konvertálható számmá.");
      }
      else{
        osszeg += (pData[i]-'0') * hatvany;
        hatvany*=10;
      }
  }
  return osszeg;
}

/*
--------------------------
*/


double String::toUnsignedDouble() const {
    double osszeg = 0.0;
  size_t i = 0;
  for (;i < len; i++){
    if (pData[i] == '.') break;
  }
  double hatvany = 0.1;
  for (size_t k = i+1; k < len; k++){
      if ((pData[k] < 48 || pData[k] > 57)) throw HibasSzam("Nem megfelelő karaktert tartalmaz a szám!");
      osszeg += ((double)(pData[k]-'0')) * hatvany;
      hatvany*=0.1;
  }
  hatvany = 1.0;
  for (int k = i-1; k >= 0; k--){
      if ((pData[k] < 48 || pData[k] > 57)) throw HibasSzam("Nem megfelelő karaktert tartalmaz a szám!");
      osszeg += ((double)(pData[k]-'0')) * hatvany;
      hatvany*=10;
  }
  return osszeg;
    /*char* vege;
    //double osszeg = strtod(pData, &vege);
    double osszeg = (double)pData;
    if (vege != &pData[len]) throw HibasSzam("Nem megfalalő karaktert tartalmaz a szám");
    if (osszeg<0) throw HibasSzam("Nem lehet negatív szám!");
    return osszeg;*/
}

String& String::operator+=(const char* s){
    len = strlen(s) + len;
    char* tmp;
    try{
    tmp = new char[len+1];
    }catch(std::bad_alloc){
      throw MemoriaHiba("Nem sikerült a stringnek memóriát foglalni");
    }
    strcpy(tmp, pData);
    strcat(tmp, s);
    tmp[len] = '\0';
    delete[] pData;
    pData = tmp;
    return (*this);
}

String& String::operator+=(const char s){
    len = 1 + len;
    char* tmp;
    try{
      tmp = new char[len+1];
    }catch(std::bad_alloc){
      throw MemoriaHiba("Nem sikerült a stringnek memóriát foglalni");
    }
    strcpy(tmp, pData);
    tmp[len-1] = s;
    tmp[len] = '\0';
    delete[] pData;
    pData = tmp;
    return (*this);
}


String& String::operator+=(const String& s){
    len = s.len + len;
    char* tmp;
    try{
      tmp = new char[len+1];
    }catch(std::bad_alloc){
      throw MemoriaHiba("Nem sikerült a stringnek memóriát foglalni");
    }
    strcpy(tmp, pData);
    strcat(tmp, s.pData);
    tmp[len] = '\0';
    delete[] pData;
    pData = tmp;
    return (*this);
}

Vektor<String> String::split(const char c) const{
        Vektor <String> tomb;
        String s;
        bool ures = true;
        for (size_t i = 0; i < len; i++){
            if (pData[i] != c) {
                s += pData[i];
            } else {
                tomb.push_back(s);
                s = "";
            }
            ures = false;
        }
        if (s != "" || ures){
          tomb.push_back(s);
        }
        return tomb;
}

/* destruktor */

String::~String(){
  delete[] pData;
}

/*
----------------------------
*/

std::ostream& operator<<(std::ostream& os, const String& s){
    for (size_t i = 0; i < s.length(); i++){
      os << s[i];
    }
    return os;
}


std::istream& operator>>(std::istream& is, String& s){
    String ujString;
    char karakter;
    while(is.get(karakter) && karakter != '\n'){
      ujString += karakter;
    }
    s = ujString;
    return is;
}