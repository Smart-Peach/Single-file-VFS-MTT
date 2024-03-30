#include "../Command.hpp"

class CreateFile: public Command {

public:
    CreateFile(str_t src_name): Command(src_name) { }
    CreateFile(const CreateFile& other) = default;
    CreateFile& operator=(CreateFile other){
        std::swap(src_name, other.src_name);
        return *this;
    }
    ~CreateFile() = default;

    void apply() override {
        std::cout << "file " << src_name << " created" << std::endl;
        return;
    }

private:
    str_t src_name;
};
