#pragma once
#include <iostream>

typedef std::string str;

class Command {
    
public:
    Command() = default;
    Command(str src_name):
        src_name(src_name) {};
    virtual ~Command() {};

    virtual void apply() {};
    
private:
    str src_name;
};

// Command::~Command() {};