#include "../Command.hpp"

class CreateFile: public Command {

public:
    CreateFile(str_t file_name): file_name(file_name) {};
    CreateFile(const CreateFile& other) = default;
    CreateFile& operator=(CreateFile other){
        std::swap(file_name, other.file_name);
        return *this;
    }
    ~CreateFile() = default;

    void apply() override {
        std::cout << "file " << file_name << " created" << std::endl;
        return;
    }

private:
    str_t file_name;
};
