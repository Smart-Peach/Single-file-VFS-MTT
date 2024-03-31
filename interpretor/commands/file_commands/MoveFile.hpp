#include "../Command.hpp"

class MoveFile: public Command {

public:
    MoveFile(str_t src_name): Command(src_name) { }
    MoveFile(const MoveFile& other) = default;
    MoveFile& operator=(MoveFile other){
        std::swap(src_name, other.src_name);
        return *this;
    }
    ~MoveFile() = default;

    void apply() override {
        std::cout << "file " << src_name << " moved" << std::endl;
        return;
    }
};