#include "../Command.hpp"

class RenameDir: public Command {

public:
    RenameDir(str_t dir_name):
        dir_name(dir_name) {};
    RenameDir(const RenameDir& other) = default;
    RenameDir& operator=(RenameDir other){
        std::swap(dir_name, other.dir_name);
        return *this;
    }
    ~RenameDir() = default;

    void apply() override {
        std::cout << "directory " << dir_name << " renamed" << std::endl;
        return;
    }

private:
    str_t dir_name;
};