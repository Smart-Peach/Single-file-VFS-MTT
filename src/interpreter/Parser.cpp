#include "includes/Parser.hpp"


// Returns pointer of Command (after parsing)
Command* Parser::next_command() {
    int next_pos = this->curr_pos;
    str_t token;

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


// Returns pointer of created Command object (gets cstr from hashmap of commands cstrs)
Command* Parser::parse(str_t token) {
    
    if (token == "create") {
        context->basic_src_name = lexer.next_token(curr_pos);
        context->mode = lexer.next_token(curr_pos);
        return two_args_funcs["create"]();
    }

    if (one_arg_funcs[token]) {
        context->basic_src_name = lexer.next_token(curr_pos);
        return one_arg_funcs[token]();

    } else if (two_args_funcs[token]) {
        context->basic_src_name = lexer.next_token(curr_pos);
        context->extra_src_name = lexer.next_token(curr_pos);
        return two_args_funcs[token]();

    } else if (data_arg_funcs[token]) {
        context->basic_src_name = lexer.next_token(curr_pos);
        context->text = lexer.next_text_token(curr_pos);
        return data_arg_funcs[token]();

    } else if (zero_args_funcs[token]) {
        return zero_args_funcs[token]();

    } else { throw InterpreterException("Unknown command '" + token + "'!");}

}
