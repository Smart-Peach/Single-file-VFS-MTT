#include "../Command.hpp"

class RenameFile: public Command {

public:
    RenameFile() = default;
    RenameFile(str file_name):
        file_name(file_name) {};
    ~RenameFile() {};

    void apply() override {
        std::cout << "file " << file_name << " renamed" << std::endl;
        return;
    }

private:
    str file_name;
};