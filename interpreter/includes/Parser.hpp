#pragma once 
#include "includes.hpp"
#include <sstream>
#include <string> 

typedef std::function<Command*(void)> cmd_cstr_t;
typedef std::vector<std::string> str_vector_t;
typedef std::string str_t;


class Parser {

public:
    Parser(Context* context, str_t input_line):
                            context(context),
                            args_pos(-1),
                            exit_flag(false)
    {
        std::istringstream iss(input_line);
        std::string token;
        while(iss >> token) { args.push_back(token); }
    };
    Parser(const Parser& other) = default;
    ~Parser() = default;

    Command* next_command();
    bool get_exit_flag();


private:
    Context* context;
    bool exit_flag;
    size_t args_pos;
    str_vector_t args;

    std::map<const str_t, cmd_cstr_t> funcs = {
    {"create", []() { return new CreateFile();}},
    {"delete", []() { return new DeleteFile();}},
    {"edit", []() { return new EditFile();}},
    {"move", []() { return new MoveFile();}},
    {"read", []() { return new ReadFile();}},
    {"rename", []() { return new RenameFile();}},
    {"seek", []() { return new SeekFile();}},
    {"write", []() { return new WriteFile();}},

    {"crtdir", []() { return new CreateDir();}},
    {"deldir", []() { return new DeleteDir();}},
    {"rdir", []() { return new ReadDir();}},
    {"rndir", []() { return new RenameDir();}},
    {"ldir", []() { return new LinkDir();}},
    {"uldir", []() { return new UnlinkDir();}}};

    Command* parse(str_t token);
    bool is_next_file();
    cmd_cstr_t get_constructor(str_t token);
};
