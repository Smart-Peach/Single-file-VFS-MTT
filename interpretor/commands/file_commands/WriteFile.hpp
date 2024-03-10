#include "../Command.hpp"

class WriteFile: public Command {

public:
    WriteFile() = default;
    WriteFile(str_t file_name):
        file_name(file_name) {};
    ~WriteFile() {};
    void apply() override {
        std::cout << "file " << file_name << " written" << std::endl;
        return;
    }

private:
    str_t file_name;
};