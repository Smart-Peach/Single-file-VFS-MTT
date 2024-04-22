#pragma once 

#include "../Command.hpp"

class Exit: public Command {
public:
    Exit(Context* ctx): Command(ctx) { }
    Exit(const Exit& other) = default;
    Exit& operator=(const Exit& other) = default;
    ~Exit() = default;

    void apply() override {
        context->finished();
    }
};