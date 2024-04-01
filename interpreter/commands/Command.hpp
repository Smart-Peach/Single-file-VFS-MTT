#pragma once

#include <iostream>

#include "../includes/Context.hpp"

typedef std::string str_t;


class Command {
public:
    virtual ~Command() { };
    virtual void apply() { }
    virtual void apply(Context* context) = 0;
    
};
