#include "includes/Interpreter.hpp"
#include "includes/Parser.hpp"

bool Interpreter::interpret(std::string input_line, FileSystem* fs){
    
    if (this->exit_flag) return false;
    Parser parser = Parser(input_line);

    while (true){
        Command* next_cmd = parser.next_command();
        if (!next_cmd || parser.get_exit_flag()) 
        {
            this->exit_flag = parser.get_exit_flag();
            break;
        }
        next_cmd->apply();
        delete next_cmd;
    }

    return !this->exit_flag;
}
