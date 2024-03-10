
#include <vector>
#include "../interpretor/Interpretor.hpp"

typedef std::vector<std::string> str_args_t;

void CommandTest(size_t test_number, str_args_t all_args, std::string excpected){
    std::cout << "--------------------- Running " << test_number << " test ---------------------" << std::endl;
    std::cout << "Excpected: \n" << excpected << std::endl;
    std::cout << "Actual:" << std::endl;
    Interpretor* interpretor = new Interpretor(all_args);
    interpretor->interpret();
}


int main(int argc, char* argv[]) {
    CommandTest(1, str_args_t {"write", "ajjajaj.a"}, "file ajjajaj.a written");
    CommandTest(2, str_args_t {"write"}, "No input file for command 'write'");
}