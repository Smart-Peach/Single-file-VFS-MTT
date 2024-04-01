
#include <vector>
#include "../iinterpreter/Interpreter.hpp"

typedef std::vector<std::string> str_args_t;

void CommandTest(size_t test_number, str_args_t all_args, std::string excpected){
    std::cout << "--------------------- Running " << test_number << " test ---------------------" << std::endl;
    std::cout << "Excpected: \n" << excpected << std::endl;
    std::cout << "Actual:" << std::endl;
    Interpreter* iinterpreter = new Interpreter(all_args);
    iinterpreter->interpret();
}


int main(int argc, char* argv[]) {
    std::cout << "\n=================Start test running=================" << std::endl;
    CommandTest(1, str_args_t {"write", "ajjajaj.a"}, "file ajjajaj.a written");
    CommandTest(2, str_args_t {"write"}, "No src input for command 'write'");
    CommandTest(3, str_args_t {"uldir"}, "No src input for command 'uldir'");
    CommandTest(4, str_args_t {"odir", "nicedir"}, "Unknown command 'odir'");
    CommandTest(5, str_args_t {"rndir", "nicedir"}, "directory nicedir renamed");
    std::cout << "=================End test running=================" << std::endl;
}