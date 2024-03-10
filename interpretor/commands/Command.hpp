#pragma once
#include <iostream>

typedef std::string str_t;

class Command {
    
public:
    virtual ~Command() {};
    virtual void apply() {};
};
