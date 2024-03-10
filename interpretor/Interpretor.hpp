#pragma once
#include "Parser.hpp"


class Interpretor {
public:

    Interpretor(str_vector_t args):
        parser(new Parser{args}),
        args(args) {};

    bool interpret();

private:
    str_vector_t args;
    Parser* parser;
};
