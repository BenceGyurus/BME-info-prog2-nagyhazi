#ifndef HIBAKEZELES_H
#define HIBAKEZELES_H

#include <stdexcept>
#include <string>

class HibasDatum : public std::invalid_argument {
public:
    HibasDatum(const char* msg): std::invalid_argument(msg){}
};

class HibasSzam : public std::invalid_argument {
public:
    HibasSzam(const char* msg): std::invalid_argument(msg){}
};

class HibasBemenet : public std::invalid_argument {
public:
    HibasBemenet(const char* msg): std::invalid_argument(msg){}
};

class FileHiba : public std::runtime_error{
public:
    FileHiba(const char* msg): std::runtime_error(msg){}
};

class MemoriaHiba : public std::runtime_error{
public:
    MemoriaHiba(const char* msg): std::runtime_error(msg){}
};


#endif
