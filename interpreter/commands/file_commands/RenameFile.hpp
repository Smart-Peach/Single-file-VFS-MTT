#include "../Command.hpp"

class RenameFile: public Command {

public:
    RenameFile(str_t src_name): Command(src_name) { }
    RenameFile(const RenameFile& other) = default;
    RenameFile& operator=(RenameFile other){
        std::swap(src_name, other.src_name);
        return *this;
    }
    ~RenameFile() = default;

    void apply() override {
        std::cout << "file " << src_name << " renamed" << std::endl;
        return;
    }
};