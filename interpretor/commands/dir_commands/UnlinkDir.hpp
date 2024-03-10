#include "../Command.hpp"

class UnlinkDir: public Command {

public:
    UnlinkDir() = default;
    UnlinkDir(str_t dir_name):
        dir_name(dir_name) {};
    ~UnlinkDir() {};

    void apply() override {
        std::cout << "directory " << dir_name << " created" << std::endl;
        return;
    }

private:
    str_t dir_name;
};