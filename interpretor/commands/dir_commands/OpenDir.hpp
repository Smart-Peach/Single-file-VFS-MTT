#include "../Command.hpp"

class OpenDir: public Command {

public:
    OpenDir(str_t dir_name):
        dir_name(dir_name) {};
    OpenDir(const OpenDir& other) = default;
    OpenDir& operator=(OpenDir other){
        std::swap(dir_name, other.dir_name);
        return *this;
    }
    ~OpenDir() = default;

    void apply() override {
        std::cout << "directory " << dir_name << " opened" << std::endl;
        return;
    }

private:
    str_t dir_name;
};