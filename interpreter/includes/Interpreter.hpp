#pragma once

#include <iostream>

#include "../../src/includes/FileSystem.hpp"
#include "context/Context.hpp"

class Interpreter {
    Context* context;

public:
    Interpreter(FileSystem* fs): context(new Context(fs)) { };
    Interpreter(const Interpreter& other) = default;
    Interpreter& operator=(const Interpreter& other) = default;
    ~Interpreter() { delete context; }

    bool interpret(std::string input_line);
};
