#include <iostream>
#include <vector>
#include "../interpretor/Interpretor.hpp"

int  main(int argc, char* argv[]){
    // test with args

    std::string current_exec_name = argv[0];
    std::vector<std::string> all_args;

    if (argc > 1) {
        all_args.assign(argv + 1, argv + argc);
        Interpretor* interpretor = new Interpretor(all_args);
        interpretor->interpret();

    } else std::cout << "No input arguments" << std::endl;


}