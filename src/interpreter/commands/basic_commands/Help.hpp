#pragma once

#include "../Command.hpp"
#include <ostream>
#include <sstream>


class Help: public Command{
public:
    Help() { }
    Help(const Help& other) = default;
    Help& operator=(const Help& other) = default;
    ~Help() = default;

    void apply(Context* context) override {
        std::fstream manual("src/interpreter/commands/basic_commands/Manual.txt");
        for (std::string line; std::getline(manual, line);) {
            std::cout << line << std::endl;
        }   
    }
};