#include "../Command.hpp"

class WriteFile: public Command {

public:
    WriteFile(str_t file_name):
        file_name(file_name) {};
    WriteFile(const WriteFile& other) = default;
    WriteFile& operator=(WriteFile other){
        std::swap(file_name, other.file_name);
        return *this;
    }
    ~WriteFile() = default;

    void apply() override {
        std::cout << "file " << file_name << " written" << std::endl;
        return;
    }

private:
    str_t file_name;
};