#pragma once
#include <iostream>

typedef std::string str_t;

class Command {
public:
    Command(str_t src_name): src_name(src_name) { }
    virtual ~Command() { }
    virtual void apply() { }
    
protected:
    str_t src_name;
};
