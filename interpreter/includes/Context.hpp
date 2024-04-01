#pragma once

#include <iostream>

#include "../../src/includes/FileSystem.hpp"

class Context {
    FileSystem* fs;
    bool exit_flag;


public:
    Context(FileSystem* fs):
            fs(fs),
            exit_flag(false) {}
    Context(const Context& context) = default;
    Context& operator=(const Context& context) = default;
    ~Context() { delete fs; };

    str_t src_name;
    str_t extra_src_name;
    
    bool get_exit_flag() { return exit_flag; }
    void set_exit_flag(bool flag) { exit_flag = flag; }
    const FileSystem* get_fs() { return fs; }
};