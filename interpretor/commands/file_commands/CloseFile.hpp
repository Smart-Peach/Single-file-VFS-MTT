#include "../Command.hpp"

class CloseFile: public Command {

public:
    CloseFile() = default;
    CloseFile(str_t file_name):
        file_name(file_name) {};
    ~CloseFile() {};

    void apply() override {
        std::cout << "file " << file_name << " closed" << std::endl;
        return;
    }

private:
    str_t file_name;
};