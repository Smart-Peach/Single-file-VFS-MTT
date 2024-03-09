#pragma once
#include "Parser.hpp"

class Interpretor {
public:
    Interpretor(std::string input_line):
        parser(new Parser{input_line}) {};

    bool interpret();

private:
    Parser* parser;
};