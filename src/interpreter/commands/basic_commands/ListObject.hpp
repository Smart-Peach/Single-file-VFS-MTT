#pragma once

#include "../Command.hpp"


class Ls: public Command{
public:
    Ls() { }
    Ls(const Ls& other) = default;
    Ls& operator=(const Ls& other) = default;
    ~Ls() = default;

    void apply(Context* context) override {
        str_t curr_dir_name = context->get_fs()->get_working_dir_name();
        for (const auto elem: context->get_fs()->get_list_of_objects_names_in_dir(curr_dir_name)) {
            std::cout << elem << " ";
        }
        std::cout << '\n';
    }
};