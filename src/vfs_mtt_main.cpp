#include <exception>
#include <sstream>
#include <string> 
#include <iostream>  
#include "interpreter/includes/Interpreter.hpp"
#include "exceptions/InterpreterException.hpp"
#include "includes/AwesomeFileSystem.hpp"
#include "includes/Superblock.hpp"
#include "includes/InodeMap.hpp"
#include "includes/types.hpp"




int main(int argc, char* argv[]){
    FileSystem* AFS = new AwesomeFileSystem(Superblock(), InodeMap(), str_t("AFS.bin"));
    Interpreter interpreter = Interpreter(AFS);
    str_t input_line;
    while (std::getline(std::cin, input_line)) {
        try {
            if (!interpreter.interpret(input_line)) break;
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }   
    }
    delete AFS;
    return 0;
}