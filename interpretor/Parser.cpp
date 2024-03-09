#include "Parser.hpp"
#include <string>

char SEPARATOR = ' ';

Command* Parser::next_command() {
    int next_pos = this->curr_pos;
    std::string token = std::string();

    while (++next_pos < input_line.length()){
        char next_sym = input_line.at(next_pos);
        if (next_sym != SEPARATOR){
             token.append(1, next_sym);
        }
        Command* cmd;
        if ((next_sym == SEPARATOR && !token.empty()) ||
             next_pos == input_line.length() - 1){
            cmd = parse(token);
        }
        else continue;
        curr_pos = next_pos;
        return cmd;
    }
    if (!token.empty()) {std::cout << "Unknown command '" << token << "'\n";};
    return nullptr;
}

Command* Parser::parse(std::string token) {
    Command* cmd = funcs[token];
    if (cmd == nullptr) {std::cout << "Unknown command '" << token << "'\n";};
    return funcs[token];
}