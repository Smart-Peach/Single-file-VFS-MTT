#include <exception>
#include <sstream>
#include <string> 
#include <iostream>  
#include "../interpreter/includes/Interpreter.hpp"
#include "exceptions/InterpreterException.hpp"
#include "includes/AwesomeFileSystem.hpp"
#include "includes/Superblock.hpp"
#include "includes/InodeMap.hpp"




int main(int argc, char* argv[]){
    Interpreter interpreter = Interpreter( new AwesomeFileSystem(Superblock(), InodeMap(), std::string("AFS.bin")));
    std::string input_line;
    while (std::getline(std::cin, input_line)) {
        try {
            if (!interpreter.interpret(input_line)) break;
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }   
    }
    return 0;
}