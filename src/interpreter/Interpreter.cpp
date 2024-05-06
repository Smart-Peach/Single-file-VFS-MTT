#include "includes/Interpreter.hpp"
#include "includes/Parser.hpp"
#include <string>

bool Interpreter::interpret(std::string input_line){
    
    if (context->get_exit_flag()) return false;
    Parser parser = Parser(context, input_line);

    while (true){
        Command* next_cmd = parser.next_command();
        if (!next_cmd || context->get_exit_flag()) 
        {
            break;
        }
        next_cmd->apply(context);
        delete next_cmd;
    }

    return !this->context->get_exit_flag();
}
