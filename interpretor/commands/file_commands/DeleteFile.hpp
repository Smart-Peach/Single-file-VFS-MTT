#include "../Command.hpp"

class DeleteFile: public Command {

public:
    DeleteFile(str_t src_name): Command(src_name) { }
    DeleteFile(const DeleteFile& other) = default;
    DeleteFile& operator=(DeleteFile other){
        std::swap(src_name, other.src_name);
        return *this;
    }
    ~DeleteFile() = default;

    void apply() override {
        std::cout << "file " << src_name << " deleted" << std::endl;
        return;
    }
};
