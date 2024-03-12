#include "../Command.hpp"

class RenameFile: public Command {

public:
    RenameFile(str_t file_name):
        file_name(file_name) {};
    RenameFile(const RenameFile& other) = default;
    RenameFile& operator=(RenameFile other){
        std::swap(file_name, other.file_name);
        return *this;
    }
    ~RenameFile() = default;

    void apply() override {
        std::cout << "file " << file_name << " renamed" << std::endl;
        return;
    }

private:
    str_t file_name;
};