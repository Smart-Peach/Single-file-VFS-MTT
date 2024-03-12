#include "../Command.hpp"

class UnlinkDir: public Command {

public:
    UnlinkDir(str_t dir_name):
        dir_name(dir_name) {};
    UnlinkDir(const UnlinkDir& other) = default;
    UnlinkDir& operator=(UnlinkDir other){
        std::swap(dir_name, other.dir_name);
        return *this;
    }
    ~UnlinkDir() = default;

    void apply() override {
        std::cout << "directory " << dir_name << " unlinked" << std::endl;
        return;
    }

private:
    str_t dir_name;
};