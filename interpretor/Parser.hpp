#pragma once 
#include <string>
#include <map>
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

class Parser {

public:
    Parser(std::string input_line):
            input_line(input_line),
            curr_pos(-1) {};
    Command* next_command();
    std::map<std::string, Command*> funcs = {
    {"create", new CreateFile()},
    {"delete", new DeleteFile()},
    {"edit", new EditFile()},
    {"move", new MoveFile()},
    {"read", new ReadFile()},
    {"rename", new RenameFile()},
    {"seek", new SeekFile()},
    {"write", new WriteFile()}
};

private:
    std::string input_line;
    size_t curr_pos;
    Command* parse(std::string token);
};
