DIR = "Dir"
FILE = "File"
HPP = ".hpp"

DIR_PATH = "interpreter/commands/dir_commands/"
FILE_PATH = "interpreter/commands/file_commands/"

if __name__ == "__main__":
    dir_cmds = ["Close", "Create", "Delete", "Link", "Open", "Read", "Rename", "Unlink"]
    file_cmds = ["Close", "Create", "Delete", "Edit", "Move", "Open", "Read", "Rename", "Seek", "Write", "AppendTo"]
    for cmd in dir_cmds:
        path = DIR_PATH + cmd + DIR
        name = cmd + DIR
        with open(path + HPP, "w") as file:
            input = f"""
#include "../Command.hpp"
#include "../../includes/context/Context.hpp"

class {name}: public Command {{
public:
    {name}(Context* ctx): Command(ctx) {{ }}
    {name}(const {name}& other) = default;
    {name}& operator=(const {name}& other) = default;
    ~{name}() = default;

    void apply() override {{
        std::cout << "{cmd + DIR} command applied to \\"" << context->get_basic_src_name() << "\\"" << std::endl;
        return;
    }}
}};"""

            file.write(input)


    for cmd in file_cmds:
        path = FILE_PATH + cmd + FILE
        name = cmd + FILE
        with open(path + HPP, "w") as file:
            input = f"""
#include "../Command.hpp"
#include "../../includes/context/Context.hpp"

class {name}: public Command {{
public:
    {name}(Context* ctx): Command(ctx) {{ }}
    {name}(const {name}& other) = default;
    {name}& operator=(const {name}& other) = default;
    ~{name}() = default;

    void apply() override {{
        std::cout << "{cmd + FILE} command applied to \\"" << context->get_basic_src_name() << "\\"" << std::endl;
        return;
    }}
}};"""

            file.write(input)
