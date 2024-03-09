#pragma once 
#include <string>
#include "/commands/Command.hpp"


// TODO: add commands for dir

struct Context {
    int parser_pos;  
};

class Parser {
public:
    Parser(std::string input_line):
            input_line(input_line),
            curr_pos(-1) {};
    
    Command* next_command();

private:
    std::string input_line;
    size_t curr_pos;
    Command* parse(std::string token);
};
