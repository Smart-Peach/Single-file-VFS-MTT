#include "../Command.hpp"

class LinkDir: public Command {

public:
    LinkDir(str_t src_name): Command(src_name) { }
    LinkDir(const LinkDir& other) = default;
    LinkDir& operator=(LinkDir other){
        std::swap(src_name, other.src_name);
        return *this;
    }
    ~LinkDir() = default;

    void apply() override {
        std::cout << "directory " << src_name << " linked" << std::endl;
        return;
    }
};