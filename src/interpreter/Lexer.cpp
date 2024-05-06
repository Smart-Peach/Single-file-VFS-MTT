#include "includes/Lexer.hpp"
#include "../exceptions/InterpreterException.hpp"

// TODO: - goto InodeMap
//       - check in inodes by hash of the name of file
//       - think about dir commands. May be better to separate cmd parser


const char SEPARATOR = ' ';

bool Lexer::contains(const str_t& str, char symbol) {
    return str.find(symbol) < str.length();
}

str_t Lexer::next_token(size_t& curr_pos) {
    int next_pos = curr_pos;
    std::string next_token = std::string();

    while (++next_pos < input_line.length()) {
        char next_sym = input_line.at(next_pos);
        if (next_sym != SEPARATOR){
             next_token.append(1, next_sym);
        }
        if ((next_sym == SEPARATOR && !next_token.empty())) break;
    }
    if (next_token.empty()) throw InterpreterException("Missed argument for command!");
    curr_pos = next_pos - 1;
    return next_token;

}

str_t Lexer::next_text_token(size_t& curr_pos) {
    std::string parsed_content = std::string();
    size_t next_pos = curr_pos;
    
    // skip spaces
    // first of all check if there is the end of line
    while (next_pos + 1 < input_line.length() && 
           input_line.at(++next_pos) == SEPARATOR); 

    // if there is the end of the line or no closing bracket after skipping spaces
    if (next_pos >= input_line.length() - 1) {
        throw InterpreterException("Missed text for command!");
    } else if (!contains(input_line.substr(next_pos + 1), '"')) {
        throw InterpreterException("Missed bracket in line!");
    } else {
        while (input_line.at(++next_pos) != '"') {
            char next_sym = input_line.at(next_pos);
            parsed_content.append(1, next_sym);
        }
    }
    curr_pos = next_pos - 1;
    return parsed_content;
}