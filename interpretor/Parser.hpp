#pragma once 
#include "includes.hpp"

typedef std::function<Command*(std::string)> cmd_cstr_t;
typedef std::vector<std::string> str_vector_t;
typedef std::string str_t;

class Parser {

public:
    // move and copy assignment operators/constructors (aka rule of 5)
    Parser(str_vector_t args):
                args(args),
                args_pos(-1),
                finished(false) {};

    Parser(const Parser& other) = default;
    Parser(Parser&& other) = default;
    Parser& operator=(Parser other){
        std::swap(args, other.args);
        std::swap(args_pos, other.args_pos);
        std::swap(finished, other.finished);
        return *this;
    } 
    ~Parser() = default;

    Command* next_command();
    bool is_finished();


private:
    bool finished;
    size_t args_pos;
    str_vector_t args;

    std::map<const str_t, cmd_cstr_t> funcs = {
    {"create", [](str_t file_name) { return new CreateFile(file_name);}},
    {"delete", [](str_t file_name) { return new DeleteFile(file_name);}},
    {"edit", [](str_t file_name) { return new EditFile(file_name);}},
    {"move", [](str_t file_name) { return new MoveFile(file_name);}},
    {"read", [](str_t file_name) { return new ReadFile(file_name);}},
    {"rename", [](str_t file_name) { return new RenameFile(file_name);}},
    {"seek", [](str_t file_name) { return new SeekFile(file_name);}},
    {"write", [](str_t file_name) { return new WriteFile(file_name);}},

    {"crtdir", [](str_t dir_name) { return new CreateDir(dir_name);}},
    {"deldir", [](str_t dir_name) { return new DeleteDir(dir_name);}},
    {"rdir", [](str_t dir_name) { return new ReadDir(dir_name);}},
    {"rndir", [](str_t dir_name) { return new RenameDir(dir_name);}},
    {"ldir", [](str_t dir_name) { return new LinkDir(dir_name);}},
    {"uldir", [](str_t dir_name) { return new UnlinkDir(dir_name);}}};

    Command* parse(str_t token);
    bool is_next_file();
    cmd_cstr_t get_constructor(str_t token);
};
