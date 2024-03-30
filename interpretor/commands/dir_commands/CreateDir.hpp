#include "../Command.hpp"

class CreateDir: public Command {

public:
    CreateDir(str_t src_name): Command(src_name) { }
    CreateDir(const CreateDir& other) = default;
    CreateDir& operator=(CreateDir other){
        std::swap(src_name, other.src_name);
        return *this;
    }
    ~CreateDir() = default;

    void apply() override {
        std::cout << "directory " << src_name << " created" << std::endl;
        return;
    }

private:
    str_t src_name;
};