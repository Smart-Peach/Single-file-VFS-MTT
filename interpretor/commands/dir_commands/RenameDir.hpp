#include "../Command.hpp"

class RenameDir: public Command {

public:
    RenameDir() = default;
    RenameDir(str_t dir_name):
        dir_name(dir_name) {};
    ~RenameDir() {};

    void apply() override {
        std::cout << "directory " << dir_name << " renamed" << std::endl;
        return;
    }

private:
    str_t dir_name;
};