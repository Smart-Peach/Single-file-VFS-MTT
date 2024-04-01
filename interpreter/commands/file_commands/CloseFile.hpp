#include "../Command.hpp"

class CloseFile: public Command {

public:
    CloseFile(str_t src_name): Command(src_name) { }
    CloseFile(const CloseFile& other) = default;
    CloseFile& operator=(CloseFile other){
        std::swap(src_name, other.src_name);
        return *this;
    }
    ~CloseFile() = default;

    void apply() override {
        std::cout << "file " << src_name << " closed" << std::endl;
        return;
    }
};