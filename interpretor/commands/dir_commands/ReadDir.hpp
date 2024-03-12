#include "../Command.hpp"

class ReadDir: public Command {

public:
    ReadDir(str_t dir_name):
        dir_name(dir_name) {};
    ReadDir(const ReadDir& other) = default;
    ReadDir& operator=(ReadDir other){
        std::swap(dir_name, other.dir_name);
        return *this;
    }
    ~ReadDir() = default;

    void apply() override {
        std::cout << "directory " << dir_name << " read" << std::endl;
        return;
    }

private:
    str_t dir_name;
};