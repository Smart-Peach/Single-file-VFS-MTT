#include "../Command.hpp"

class EditFile: public Command {

public:
    EditFile(str_t src_name): Command(src_name) { }
    EditFile(const EditFile& other) = default;
    EditFile& operator=(EditFile other){
        std::swap(src_name, other.src_name);
        return *this;
    }
    ~EditFile() = default;

    void apply() override {
        std::cout << "file " << src_name << " edited" << std::endl;
        return;
    }
};