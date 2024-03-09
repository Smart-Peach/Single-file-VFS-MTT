#include "Interpretor.hpp"

bool Interpretor::interpret(){
    while (true){
        Command* next_cmd = parser->next_command();
        if (next_cmd == nullptr) break;
        next_cmd->apply();
    }
    return 1;
}