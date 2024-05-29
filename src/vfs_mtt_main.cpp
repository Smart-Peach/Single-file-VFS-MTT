#include <exception>
#include <sstream>
#include <string> 
#include <iostream>  

#include "interpreter/includes/Interpreter.hpp"
#include "exceptions/InterpreterException.hpp"
#include "includes/AwesomeFileSystem.hpp"
#include "includes/LoaderBinFile.hpp"
#include "includes/Superblock.hpp"
#include "includes/InodeMap.hpp"
#include "includes/types.hpp"




int main(int argc, char* argv[]){
    Loader* loader = new LoaderBinFile(str_t("AFS.bin"));
    // size_t add = 0;
    // loader->write_char(add, 'a');

    // FileSystem* AFS = new AwesomeFileSystem(Superblock(), InodeMap(), str_t("AFS.bin"));
    std::cout << "Before making file system\n";
    FileSystem* AFS = new AwesomeFileSystem(loader);
    Interpreter interpreter = Interpreter(AFS);
    str_t input_line;
    std::cout << "Start interpreter\n";
    while (std::getline(std::cin, input_line)) {
        try {
            if (!interpreter.interpret(input_line)) break;
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }   
    }
    delete AFS;
    delete loader;
    return 0;
}