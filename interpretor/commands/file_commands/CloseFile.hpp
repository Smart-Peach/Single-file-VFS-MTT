#include "../Command.hpp"

class CloseFile: public Command {

public:
    CloseFile() = default;
    CloseFile(str file_name):
        file_name(file_name) {};

    void apply() override {
        std::cout << "file " << file_name << " closed" << std::endl;
        return;
    }

private:
    str file_name;
};