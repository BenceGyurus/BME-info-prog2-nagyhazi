#include "vezerles.h"
#include "string.h"
#include "test.h"

int main(int argc, char* argv[]){
    #ifdef CPORTA
        test();
        Vezerles vezerles("adatok.csv");
        vezerles.run();
    #endif
    #ifndef CPORTA
    bool menuFlag = false;
    for (int i = 1; i < argc; ++i) {
        String arg = argv[i];
        if (arg == "-menu") {
            menuFlag = true;
        }
    }
    if (!menuFlag){
        test();
    }else{
        try{
            Vezerles vezerles("adatok.csv");
            vezerles.run();
        }catch(std::runtime_error& error){
            std::cout << "[FUTÁSI HIBA] " << error.what() << std::endl;
        }
    }
    #endif
}