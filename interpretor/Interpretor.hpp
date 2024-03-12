#pragma once
#include "Parser.hpp"
#include <utility>


class Interpretor {
public:

    Interpretor(str_vector_t args):
            parser(new Parser{args}),
            args(args) {};
    Interpretor(const Interpretor& other) = default;
    Interpretor& operator=(Interpretor other){
        std::swap(args, other.args);
        std::swap(parser, other.parser);
        return *this;
    }
    ~Interpretor() {delete parser;};

    bool interpret();

private:
    str_vector_t args;
    Parser* parser;
};
