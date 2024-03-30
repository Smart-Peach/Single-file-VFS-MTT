#include "../Command.hpp"

class RenameDir: public Command {

public:
    RenameDir(str_t src_name): Command(src_name) { }
    RenameDir(const RenameDir& other) = default;
    RenameDir& operator=(RenameDir other){
        std::swap(src_name, other.src_name);
        return *this;
    }
    ~RenameDir() = default;

    void apply() override {
        std::cout << "directory " << src_name << " renamed" << std::endl;
        return;
    }

private:
    str_t src_name;
};