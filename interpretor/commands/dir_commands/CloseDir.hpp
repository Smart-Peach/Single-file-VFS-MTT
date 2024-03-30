#include "../Command.hpp"

class CloseDir: public Command {

public:
    CloseDir(str_t src_name): Command(src_name) { }
    CloseDir(const CloseDir& other) = default;
    CloseDir& operator=(CloseDir other){
        std::swap(src_name, other.src_name);
        return *this;
    }
    ~CloseDir() = default;

    void apply() override {
        std::cout << "directory " << src_name << " closed" << std::endl;
        return;
    }

private:
    str_t src_name;
};