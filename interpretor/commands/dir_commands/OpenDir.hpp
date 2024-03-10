#include "../Command.hpp"

class OpenDir: public Command {

public:
    OpenDir() = default;
    OpenDir(str_t dir_name):
        dir_name(dir_name) {};
    ~OpenDir() {};

    void apply() override {
        std::cout << "directory " << dir_name << " opened" << std::endl;
        return;
    }

private:
    str_t dir_name;
};