#pragma once

#include <iostream>
#include "../../src/includes/FileSystem.hpp"
#include "Context.hpp"

class Interpreter {
    bool exit_flag = false;
    Context* context;

public:
    Interpreter(FileSystem* fs): context(new Context(fs)) { };
    Interpreter(const Interpreter& other) = default;
    Interpreter& operator=(const Interpreter& other) = default;
    ~Interpreter() { delete context;};

    bool interpret(std::string input_line);
    bool get_exit_flag() { return exit_flag; }

};
