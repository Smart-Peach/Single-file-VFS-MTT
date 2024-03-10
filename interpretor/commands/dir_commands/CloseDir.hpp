#include "../Command.hpp"

class CloseDir: public Command {

public:
    CloseDir() = default;
    CloseDir(str_t dir_name):
        dir_name(dir_name) {};
    ~CloseDir() {};

    void apply() override {
        std::cout << "directory " << dir_name << " closed" << std::endl;
        return;
    }

private:
    str_t dir_name;
};