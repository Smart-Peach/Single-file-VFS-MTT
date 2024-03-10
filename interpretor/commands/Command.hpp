#pragma once
#include <iostream>

typedef std::string str;

class Command {
    
public:
    Command() = default;
    Command(str src_name):
        src_name(src_name) {};

    virtual void apply() = 0;
    
private:
    str src_name;
};