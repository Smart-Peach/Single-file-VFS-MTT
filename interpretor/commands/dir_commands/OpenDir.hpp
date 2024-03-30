#include "../Command.hpp"

class OpenDir: public Command {

public:
    OpenDir(str_t src_name): Command(src_name) { }
    OpenDir(const OpenDir& other) = default;
    OpenDir& operator=(OpenDir other){
        std::swap(src_name, other.src_name);
        return *this;
    }
    ~OpenDir() = default;

    void apply() override {
        std::cout << "directory " << src_name << " opened" << std::endl;
        return;
    }

private:
    str_t src_name;
};