#pragma once
#include "Parser.hpp"

class Interpretor {
public:
    Interpretor(std::string input_line):
        parser(new Parser{input_line}) {};

    bool interpret(std::string input_line);

private:
    Parser* parser;
};