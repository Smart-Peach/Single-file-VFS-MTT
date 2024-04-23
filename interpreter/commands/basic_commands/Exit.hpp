#pragma once 

#include "../Command.hpp"

class Exit: public Command {
public:
    Exit() { }
    Exit(const Exit& other) = default;
    Exit& operator=(const Exit& other) = default;
    ~Exit() = default;

    void apply(Context* context) override {
        context->finished();
    }
};