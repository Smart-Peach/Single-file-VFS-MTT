#include "../Command.hpp"

class WriteFile: public Command {

public:
    WriteFile() = default;
    WriteFile(str file_name):
        file_name(file_name) {};
    void apply() override {
        std::cout << "file " << file_name << " written" << std::endl;
        return;
    }

private:
    str file_name;
};