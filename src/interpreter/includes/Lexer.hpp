#pragma once 

// #include "includes.hpp"
#include "../../includes/types.hpp" 

#include <iostream>

class Parser;

class Lexer {
    
    friend Parser;
    str_t input_line;

    static bool contains(const str_t& str, char symbol);
    str_t next_token(size_t& curr_pos);
    str_t next_text_token(size_t& curr_pos);

public:
    Lexer(str_t input_line): input_line(input_line) { }
    ~Lexer() { }
};