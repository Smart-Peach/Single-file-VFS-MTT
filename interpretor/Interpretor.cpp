#include "Interpretor.hpp"

bool Interpretor::interpret(){
    if (parser->is_finished()) return true;
    while (true){
        Command* next_cmd = parser->next_command();
        if (next_cmd == nullptr) break;
        next_cmd->apply();
    }
    return true;
}
