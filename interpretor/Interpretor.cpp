#include "Interpretor.hpp"

bool Interpretor::interpret(std::string input_line){
    while (true){
        Command* next_cmd = parser->next_command();
        if (!next_cmd) break;
        next_cmd->apply();
    }
    return 1;
}