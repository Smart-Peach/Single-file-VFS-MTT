#include "../Command.hpp"

class CloseDir: public Command {

public:
    CloseDir(str_t dir_name):
        dir_name(dir_name) {};
    CloseDir(const CloseDir& other) = default;
    CloseDir& operator=(CloseDir other){
        std::swap(dir_name, other.dir_name);
        return *this;
    }
    ~CloseDir() = default;

    void apply() override {
        std::cout << "directory " << dir_name << " closed" << std::endl;
        return;
    }

private:
    str_t dir_name;
};