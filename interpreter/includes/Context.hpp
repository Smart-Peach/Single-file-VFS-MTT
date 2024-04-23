#pragma once

#include "../../src/includes/FileSystem.hpp"


class Command;
class Parser;

class Context {
    friend Command;
    friend Parser;

    FileSystem* fs;
    bool exit_flag;

    str_t basic_src_name;
    str_t extra_src_name;
    str_t text;

public:
    Context(FileSystem* fs): fs(fs),
                             exit_flag(false) { }
    virtual ~Context() { }

    bool get_exit_flag() { return exit_flag; }
    str_t get_basic_src_name() { return basic_src_name; }
    str_t get_extra_src_name() { return extra_src_name; }
    str_t get_text() { return text; }
    const FileSystem* get_fs() { return fs; }
    void finished() { exit_flag = true; }
};