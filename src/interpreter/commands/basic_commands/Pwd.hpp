#pragma once

#include "../Command.hpp"


class Pwd: public Command{
public:
    Pwd() { }
    Pwd(const Pwd& other) = default;
    Pwd& operator=(const Pwd& other) = default;
    ~Pwd() = default;

    void apply(Context* context) override {
        std::cout << "Current working directory: \"" << context->get_fs()->get_working_dir_name() << "\"" << std::endl;
    }
};