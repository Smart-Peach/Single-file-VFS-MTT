#pragma once

#include "../Command.hpp"


class Ls: public Command{
public:
    Ls() { }
    Ls(const Ls& other) = default;
    Ls& operator=(const Ls& other) = default;
    ~Ls() = default;

    void apply(Context* context) override {
        // for (const auto elem: context->get_fs(). )
        std::cout << "Current working directory: " << context->get_fs()->get_working_dir_name() << std::endl;
    }
};