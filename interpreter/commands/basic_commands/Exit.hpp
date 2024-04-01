#pragma once 

#include "../Command.hpp"

class Exit: public Command {
public:
    Exit() { }
    Exit(const Exit& other) = default;
    Exit& operator=(const Exit& other) = default;
    ~Exit() = default;

    void apply() override {
        std::cout << "Exit 0" << std::endl;
        return;
    }
};