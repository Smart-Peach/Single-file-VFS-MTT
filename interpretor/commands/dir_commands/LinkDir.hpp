#include "../Command.hpp"

class LinkDir: public Command {

public:
    LinkDir(str_t dir_name):
        dir_name(dir_name) {};
    LinkDir(const LinkDir& other) = default;
    LinkDir& operator=(LinkDir other){
        std::swap(dir_name, other.dir_name);
        return *this;
    }
    ~LinkDir() = default;

    void apply() override {
        std::cout << "directory " << dir_name << " linked" << std::endl;
        return;
    }

private:
    str_t dir_name;
};