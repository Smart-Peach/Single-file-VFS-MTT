#include "../Command.hpp"

class CreateFile: public Command {

public:
    CreateFile() = default;
    CreateFile(str_t file_name):
        file_name(file_name) {};
    ~CreateFile() {};

    void apply() override {
        std::cout << "file " << file_name << " created" << std::endl;
        return;
    }

private:
    str_t file_name;
};
