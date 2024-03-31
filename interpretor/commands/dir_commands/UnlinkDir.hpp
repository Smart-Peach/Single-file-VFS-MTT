#include "../Command.hpp"

class UnlinkDir: public Command {

public:
    UnlinkDir(str_t src_name): Command(src_name) { }
    UnlinkDir(const UnlinkDir& other) = default;
    UnlinkDir& operator=(UnlinkDir other){
        std::swap(src_name, other.src_name);
        return *this;
    }
    ~UnlinkDir() = default;

    void apply() override {
        std::cout << "directory " << src_name << " unlinked" << std::endl;
        return;
    }
};