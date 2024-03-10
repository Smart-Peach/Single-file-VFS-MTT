#pragma once 
#include <functional>
#include <string>
#include <map>
#include <vector>
#include "commands/Command.hpp"
#include "commands/file_commands/CreateFile.hpp"
#include "commands/file_commands/DeleteFile.hpp"
#include "commands/file_commands/EditFile.hpp"
#include "commands/file_commands/MoveFile.hpp"
#include "commands/file_commands/ReadFile.hpp"
#include "commands/file_commands/RenameFile.hpp"
#include "commands/file_commands/SeekFile.hpp"
#include "commands/file_commands/WriteFile.hpp"
#include "commands/dir_commands/CreateDir.hpp"
#include "commands/dir_commands/DeleteDir.hpp"
#include "commands/dir_commands/ReadDir.hpp"
#include "commands/dir_commands/RenameDir.hpp"
#include "commands/dir_commands/LinkDir.hpp"
#include "commands/dir_commands/UnlinkDir.hpp"

// TODO: add commands for dir

typedef std::function<Command*(std::string)> cmd_cstr_t;
typedef std::vector<std::string> str_vector_t;
typedef std::string str_t;

class Parser {

public:
    Parser(str_vector_t args):
        args(args),
        args_pos(-1),
        finished(false) {};
    ~Parser() {};

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
