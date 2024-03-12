#include "../Command.hpp"

class DeleteFile: public Command {

public:
    DeleteFile(str_t file_name):
        file_name(file_name) {};
    DeleteFile(const DeleteFile& other) = default;
    DeleteFile& operator=(DeleteFile other){
        std::swap(file_name, other.file_name);
        return *this;
    }
    ~DeleteFile() = default;

    void apply() override {
        std::cout << "file " << file_name << " deleted" << std::endl;
        return;
    }

private:
    str_t file_name;
};
