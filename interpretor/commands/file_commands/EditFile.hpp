#include "../Command.hpp"

class EditFile: public Command {

public:
    EditFile() = default;
    EditFile(str_t file_name):
        file_name(file_name) {};
    ~EditFile() {};

    void apply() override {
        std::cout << "file " << file_name << " edited" << std::endl;
        return;
    }

private:
    str_t file_name;
};