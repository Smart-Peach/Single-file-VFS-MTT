#include "../Command.hpp"

class DeleteDir: public Command {

public:
    DeleteDir() = default;
    DeleteDir(str_t dir_name):
        dir_name(dir_name) {};
    ~DeleteDir() {};

    void apply() override {
        std::cout << "directory " << dir_name << " deleted" << std::endl;
        return;
    }

private:
    str_t dir_name;
};