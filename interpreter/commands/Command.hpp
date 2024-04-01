#pragma once
#include <iostream>
#include "../../src/includes/FileSystem.hpp"

typedef std::string str_t;

class Command {
public:
    Command() { }
    Command(str_t src_name): src_name(src_name) { }
    virtual ~Command() { }
    virtual void apply() { }
    virtual void apply(FileSystem* fs) { }
    
protected:
    str_t src_name;
};
