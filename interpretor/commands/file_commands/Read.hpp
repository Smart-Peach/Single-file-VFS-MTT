#include "../Command.hpp"

class ReadFile: public Command {

public:
    ReadFile() = default;
    ReadFile(str file_name):
        file_name(file_name) {};
    ~ReadFile() {};

    void apply() override {
        std::cout << "file " << file_name << " read" << std::endl;
        return;
    }

private:
    str file_name;
};