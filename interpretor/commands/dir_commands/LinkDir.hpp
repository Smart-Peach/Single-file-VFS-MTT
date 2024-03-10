#include "../Command.hpp"

class LinkDir: public Command {

public:
    LinkDir() = default;
    LinkDir(str_t dir_name):
        dir_name(dir_name) {};
    ~LinkDir() {};

    void apply() override {
        std::cout << "directory " << dir_name << " linked" << std::endl;
        return;
    }

private:
    str_t dir_name;
};