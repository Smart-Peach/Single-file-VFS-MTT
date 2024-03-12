#include "../Command.hpp"

class EditFile: public Command {

public:
    EditFile(str_t file_name):
        file_name(file_name) {};
    EditFile(const EditFile& other) = default;
    EditFile& operator=(EditFile other){
        std::swap(file_name, other.file_name);
        return *this;
    }
    ~EditFile() = default;

    void apply() override {
        std::cout << "file " << file_name << " edited" << std::endl;
        return;
    }

private:
    str_t file_name;
};