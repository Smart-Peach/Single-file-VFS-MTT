#include "../Command.hpp"

class CreateDir: public Command {

public:
    CreateDir(str_t dir_name):
        dir_name(dir_name) {};
    CreateDir(const CreateDir& other) = default;
    CreateDir& operator=(CreateDir other){
        std::swap(dir_name, other.dir_name);
        return *this;
    }
    ~CreateDir() = default;

    void apply() override {
        std::cout << "directory " << dir_name << " created" << std::endl;
        return;
    }

private:
    str_t dir_name;
};