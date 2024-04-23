#include "includes/Parser.hpp"
#include "../src/exceptions/InterpreterException.hpp"
#include <functional>
#include <string> 

char SEPARATOR = ' ';

// Returns pointer of Command (after parsing)
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
            // TODO: simplify
            curr_pos = next_pos;
            cmd = parse(token);
            next_pos = curr_pos + 1;
        }
        else continue;
        curr_pos = next_pos;
        return cmd;
    }
    if (!token.empty()) {std::cout << "Unknown command '" << token << "'\n";};
    return nullptr;
}


// TODO: - goto InodeMap
//       - check in inodes by hash of the name of file
//       - think about dir commands. May be better to separate cmd parser


bool Parser::contains(const str_t& str, char symbol) {
    return str.find(symbol) < str.length();
}


str_t Parser::next_token(size_t sym_pos) {

    int next_pos = sym_pos;
    std::string next_token = std::string();

    while (++next_pos < input_line.length()) {
        char next_sym = input_line.at(next_pos);
        if (next_sym != SEPARATOR){
             next_token.append(1, next_sym);
        }
        if ((next_sym == SEPARATOR && !next_token.empty())) break;
    }
    if (next_token.empty()) throw InterpreterException("Missed argument for command!");
    curr_pos = next_pos;
    return next_token;

}

str_t Parser::parse_text(size_t sym_pos) {
    std::string parsed_content = std::string();
    size_t next_pos = sym_pos;
    
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
    curr_pos = next_pos;
    return parsed_content;
}

// Returns pointer of created Command object (gets cstr from hashmap of commands cstrs)
Command* Parser::parse(str_t token) {

    if (one_arg_funcs[token]) {
        context->basic_src_name = next_token(curr_pos);
        return one_arg_funcs[token]();

    } else if (two_args_funcs[token]) {
        context->basic_src_name = next_token(curr_pos);
        context->extra_src_name = next_token(curr_pos);
        return two_args_funcs[token]();

    } else if (data_arg_funcs[token]) {
        context->basic_src_name = next_token(curr_pos);
        context->text = parse_text(curr_pos);
        return data_arg_funcs[token]();

    } else if (zero_args_funcs[token]) {
        return zero_args_funcs[token]();

    } else { throw InterpreterException("Unknown command '" + token + "'!");}

}
