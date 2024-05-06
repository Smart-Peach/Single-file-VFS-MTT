#pragma once

#include "../includes/Context.hpp"

typedef std::string str_t;

class Command {
protected:

public:
    virtual ~Command() { };
    virtual void apply(Context* ctx) = 0;
    
};
