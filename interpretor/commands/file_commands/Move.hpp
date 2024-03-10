#include "../Command.hpp"

class MoveFile: public Command {

public:
    MoveFile() = default;
    MoveFile(str file_name):
        file_name(file_name) {};
    ~MoveFile() {};

    void apply() override {
        std::cout << "file " << file_name << " moved" << std::endl;
        return;
    }

private:
    str file_name;
};