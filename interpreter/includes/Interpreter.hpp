#pragma once

#include <iostream>
#include "../../src/includes/FileSystem.hpp"

class Interpreter {
    bool exit_flag = false;

public:
    Interpreter() { };
    Interpreter(const Interpreter& other) = default;
    Interpreter& operator=(const Interpreter& other) = default;
    ~Interpreter() = default;

    bool interpret(std::string input_line, FileSystem* fs);
    bool get_exit_flag() { return exit_flag; }

};
