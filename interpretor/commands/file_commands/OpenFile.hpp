#include "../Command.hpp"

class OpenFile: public Command {

public:
    OpenFile(str_t file_name):
        file_name(file_name) {};
    OpenFile(const OpenFile& other) = default;
    OpenFile& operator=(OpenFile other){
        std::swap(file_name, other.file_name);
        return *this;
    }
    ~OpenFile() = default;

    void apply() override {
        std::cout << "file " << file_name << " opened" << std::endl;
        return;
    }

private:
    str_t file_name;
};