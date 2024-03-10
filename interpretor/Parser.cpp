#include "Parser.hpp"

bool Parser::is_finished(){ return finished;}

Command* Parser::next_command() {

    if (args_pos == args.size() - 1) {
        finished = true;
        return nullptr;
    }
    int next_arg = args_pos;
    if (++next_arg == args.size() - 1){
        finished = true;
    }
    args_pos = next_arg;
    return parse(args[next_arg]);
}


cmd_cstr_t Parser::get_constructor(str_t token) {
    return funcs[token];
}

// TODO: check in db if file exists
// TODO: think about dir commands. May be better to separate cmd parser

bool Parser::is_next_file() {
    if (args_pos + 1 < args.size()){
        str_t token = args.at(args_pos + 1);
        return !get_constructor(token);
    }
    return false;
}


Command* Parser::parse(str_t token) {

    if (!get_constructor(token)) {
        std::cout << "Unknown command '" << token << "'\n";
        return nullptr;
    } else if (is_next_file()){
        return get_constructor(token)(args.at(++args_pos));
    } else {
        std::cout << "No src input for command '" << token << "'\n";
        return nullptr;
    }
}