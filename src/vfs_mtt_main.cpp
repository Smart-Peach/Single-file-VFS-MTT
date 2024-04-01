#include <sstream>
#include <string> 
#include <iostream>  
#include "../interpreter/includes/Interpreter.hpp"
#include "exceptions/InterpreterException.hpp"

int  main(int argc, char* argv[]){
    
    Interpreter interpreter = Interpreter();
    std::string input_line;
    while (std::getline(std::cin, input_line)) {
        try {
            if (!interpreter.interpret(input_line)) break;
        } catch (const InterpreterException& e) {
            std::cerr << e.what() << std::endl;
        }   
    }
    return 0;
}