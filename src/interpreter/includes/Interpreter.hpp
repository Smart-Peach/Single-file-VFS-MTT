#pragma once


#include "../../includes/FileSystem.hpp"
#include "../../includes/types.hpp" 
#include "Context.hpp"

class Interpreter {
    Context* context;

public:
    Interpreter(FileSystem* fs): context(new Context(fs)) { };
    Interpreter(const Interpreter& other) = default;
    Interpreter& operator=(const Interpreter& other) = default;
    ~Interpreter() { delete context; }

    bool interpret(str_t input_line);
};
