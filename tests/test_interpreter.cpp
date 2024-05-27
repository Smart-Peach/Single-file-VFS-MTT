
#include <sstream> 
#include <cassert>

#include "../src/interpreter/includes/Interpreter.hpp"
#include "../src/includes/AwesomeFileSystem.hpp"
#include "../src/exceptions/InterpreterException.hpp"


void CommandTest(FileSystem* AFS, size_t test_number, std::string input_line, std::string excpected){
    std::cout << "--------------------- Running " << test_number << " test ---------------------" << std::endl;

    std::stringstream ss;
    std::streambuf *coutbuf = std::cout.rdbuf(); // save old buffer
    std::cout.rdbuf(ss.rdbuf()); // redirect std::cout to ss
    
    Interpreter interpreter = Interpreter(AFS);
    try {
        interpreter.interpret(input_line);
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    std::cout.rdbuf(coutbuf); // reset to standard output again


    std::string actual = ss.str();
    std::cout << "Command line: " << input_line << std::endl;
    std::cout << "Excpected: " << excpected << std::endl;
    std::cout << "Actual: " << actual << std::endl;
    assert(excpected + '\n' == actual);
    std::cout << "TEST PASSED" << std::endl;
}


int main(int argc, char* argv[]) {

    FileSystem* AFS =  new AwesomeFileSystem(Superblock(), InodeMap(), std::string("tests/test.bin"));

    std::cout << "\n=================Start test running=================" << std::endl;
    CommandTest(AFS, 1, "write ajjajaj.a", "Missed text for command!");
    CommandTest(AFS, 2, "write", "Missed argument for command!");
    CommandTest(AFS, 3, "cd", "Missed argument for command!");
    CommandTest(AFS, 4,"odir nicedir", "Unknown command 'odir'!");
    CommandTest(AFS, 5,"create file.txt write file.txt \"nice message\"", "CreateFile command was applied to \"file.txt\"\nWriteFile command was applied to \"file.txt\"\nText: nice message");
    CommandTest(AFS, 6,"create file1.txt delete file1.txt", "CreateFile command was applied to \"file1.txt\"\nDeleteFile command was applied to \"file1.txt\"");
    CommandTest(AFS, 7,"crtdir nice_dir", "CreateDir command was applied to \"nice_dir\"");
    CommandTest(AFS, 8,"cd nice_dir", "ChangeDir command was applied to \"nice_dir\"");
    CommandTest(AFS, 9,"pwd", "Current working directory: \"root/nice_dir\"");
    CommandTest(AFS, 9,"cd .. pwd", "ChangeDir command was applied to \"..\"\nCurrent working directory: \"root\"");
    CommandTest(AFS, 10,"deldir nice_dir", "DeleteDir command was applied to \"nice_dir\"");
    CommandTest(AFS, 11,"deldir nice_dir", "Directory \"nice_dir\" does not exist!");

    std::cout << "=================End test running=================" << std::endl;

    delete AFS;
}