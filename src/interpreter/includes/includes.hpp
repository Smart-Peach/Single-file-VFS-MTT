#pragma once

#include <iostream>
#include <functional>
#include <map>
#include <vector>
#include "../commands/Command.hpp"
#include "Context.hpp"
#include "../commands/file_commands/CreateFile.hpp"
#include "../commands/file_commands/DeleteFile.hpp"
#include "../commands/file_commands/EditFile.hpp"
#include "../commands/file_commands/MoveFile.hpp"
#include "../commands/file_commands/ReadFile.hpp"
#include "../commands/file_commands/RenameFile.hpp"
#include "../commands/file_commands/WriteFile.hpp"
#include "../commands/file_commands/AppendToFile.hpp"
#include "../commands/dir_commands/CreateDir.hpp"
#include "../commands/dir_commands/DeleteDir.hpp"
#include "../commands/dir_commands/ReadDir.hpp"
#include "../commands/dir_commands/RenameDir.hpp"
#include "../commands/dir_commands/LinkDir.hpp"
#include "../commands/dir_commands/UnlinkDir.hpp"
#include "../commands/basic_commands/Exit.hpp"

#include "../../exceptions/InterpreterException.hpp"

typedef std::string str_t;
static char SEPARATOR = ' ';