
#include "includes/Parser.hpp"
#include "../src/exceptions/InterpreterException.hpp"
#include <iostream>

bool Parser::get_exit_flag(){ return exit_flag; }

// Returns pointer of Command (after parsing)
Command* Parser::next_command() {
    if (args_pos == args.size() - 1) {
        return nullptr;
    }
    return parse(args[++args_pos]);
}

// Returns lamda-expression (constructor) from hashmap of cstrs
cmd_cstr_t Parser::get_constructor(str_t token) {
    return funcs[token];
}


// TODO: - goto InodeMap
//       - check in inodes by hash of the name of file
//       - think about dir commands. May be better to separate cmd parser


// Takes current position in args, checks in InodeMap wheter next argument is existing file
bool Parser::is_next_file() {
    if (args_pos + 1 < args.size()){
        str_t token = args.at(args_pos + 1);
        return !get_constructor(token);
    }
    return false;
}

// TODO: - consider difference btw commands
//       - add parsing of command - cmd <name> "name"
//       - mb add fields to such cmds   
//       - parse some basic commands (in future)  


// Returns pointer of created Command object (gets cstr from hashmap of commands cstrs)
Command* Parser::parse(str_t token) {
    if (token.compare("exit") == 0) {
        exit_flag = true;
        return nullptr;
    }
    if (!get_constructor(token)) {
        throw new InterpreterException("Unknown command '" + token + "'");
    } else if (is_next_file()){
        return get_constructor(token)(args.at(++args_pos));
    } else {
        throw new InterpreterException("No src input for command '" + token + "'");
    }
}