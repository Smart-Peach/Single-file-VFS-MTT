#include "../Command.hpp"

class ReadDir: public Command {

public:
    ReadDir() = default;
    ReadDir(str_t dir_name):
        dir_name(dir_name) {};
    ~ReadDir() {};

    void apply() override {
        std::cout << "directory " << dir_name << " created" << std::endl;
        return;
    }

private:
    str_t dir_name;
};