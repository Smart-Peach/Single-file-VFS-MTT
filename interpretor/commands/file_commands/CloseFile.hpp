#include "../Command.hpp"

class CloseFile: public Command {

public:
    CloseFile(str_t file_name):
        file_name(file_name) {};
    CloseFile(const CloseFile& other) = default;
    CloseFile& operator=(CloseFile other){
        std::swap(file_name, other.file_name);
        return *this;
    }
    ~CloseFile() = default;

    void apply() override {
        std::cout << "file " << file_name << " closed" << std::endl;
        return;
    }

private:
    str_t file_name;
};