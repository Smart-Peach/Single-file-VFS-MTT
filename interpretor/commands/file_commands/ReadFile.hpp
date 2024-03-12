#include "../Command.hpp"

class ReadFile: public Command {

public:
    ReadFile(str_t file_name):
        file_name(file_name) {};
    ReadFile(const ReadFile& other) = default;
    ReadFile& operator=(ReadFile other){
        std::swap(file_name, other.file_name);
        return *this;
    }
    ~ReadFile() = default;

    void apply() override {
        std::cout << "file " << file_name << " read" << std::endl;
        return;
    }

private:
    str_t file_name;
};