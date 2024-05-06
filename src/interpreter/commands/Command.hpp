#pragma once

#include "../includes/Context.hpp"
#include "../../includes/types.hpp" 

class Command {
protected:

public:
    virtual ~Command() { };
    virtual void apply(Context* ctx) = 0;
    
};
