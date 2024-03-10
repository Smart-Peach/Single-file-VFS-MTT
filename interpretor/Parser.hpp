#pragma once 
#include <functional>
#include <string>
#include <map>
#include <vector>
#include "commands/Command.hpp"
#include "commands/file_commands/Create.hpp"
#include "commands/file_commands/Delete.hpp"
#include "commands/file_commands/Edit.hpp"
#include "commands/file_commands/Move.hpp"
#include "commands/file_commands/Read.hpp"
#include "commands/file_commands/Rename.hpp"
#include "commands/file_commands/Seek.hpp"
#include "commands/file_commands/Write.hpp"

// TODO: add commands for dir

typedef std::function<Command*(std::string)> cmd_cstr_t;
typedef std::vector<std::string> str_vector_t;
typedef std::string str;

class Parser {

public:
    Parser(str_vector_t args):
        args(args),
        args_pos(-1),
        finished(false) {};

    Command* next_command();
    bool is_finished();


private:
    bool finished;
    size_t args_pos;
    str_vector_t args;
    std::map<const str, cmd_cstr_t> funcs = {
    {"create", [](str file_name) { return new CreateFile(file_name);}},
    {"delete", [](str file_name) { return new DeleteFile(file_name);}},
    {"edit", [](str file_name) { return new EditFile(file_name);}},
    {"move", [](str file_name) { return new MoveFile(file_name);}},
    {"read", [](str file_name) { return new ReadFile(file_name);}},
    {"rename", [](str file_name) { return new RenameFile(file_name);}},
    {"seek", [](str file_name) { return new SeekFile(file_name);}},
    {"write", [](str file_name) { return new WriteFile(file_name);}}};

    Command* parse(str token);
    bool is_next_file();
    cmd_cstr_t get_constructor(str token);
};
