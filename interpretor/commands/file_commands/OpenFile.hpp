#include "../Command.hpp"

class OpenFile: public Command {

public:
    OpenFile() = default;
    OpenFile(str file_name):
        file_name(file_name) {};
    void apply() override {
        std::cout << "file " << file_name << " opened" << std::endl;
        return;
    }

private:
    str file_name;
};