#include "../Command.hpp"

class EditFile: public Command {

public:
    EditFile() = default;
    EditFile(str file_name):
        file_name(file_name) {};
    void apply() override {
        std::cout << "file " << file_name << " edited" << std::endl;
        return;
    }

private:
    str file_name;
};