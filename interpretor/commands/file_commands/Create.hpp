#include "../Command.hpp"

class CreateFile: public Command {

public:
    CreateFile() = default;
    CreateFile(str file_name):
        file_name(file_name) {};

    void apply() override {
        std::cout << "file " << file_name << " created" << std::endl;
        return;
    }

private:
    str file_name;
};
