#include "../Command.hpp"

class OpenFile: public Command {

public:
    OpenFile() = default;
    OpenFile(str_t file_name):
        file_name(file_name) {};
    ~OpenFile() {};

    void apply() override {
        std::cout << "file " << file_name << " opened" << std::endl;
        return;
    }

private:
    str_t file_name;
};