#include "../Command.hpp"

class MoveFile: public Command {

public:
    MoveFile(str_t file_name):
        file_name(file_name) {};
    MoveFile(const MoveFile& other) = default;
    MoveFile& operator=(MoveFile other){
        std::swap(file_name, other.file_name);
        return *this;
    }
    ~MoveFile() = default;

    void apply() override {
        std::cout << "file " << file_name << " moved" << std::endl;
        return;
    }

private:
    str_t file_name;
};