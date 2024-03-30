#include "../Command.hpp"

class OpenFile: public Command {

public:
    OpenFile(str_t src_name): Command(src_name) { }
    OpenFile(const OpenFile& other) = default;
    OpenFile& operator=(OpenFile other){
        std::swap(src_name, other.src_name);
        return *this;
    }
    ~OpenFile() = default;

    void apply() override {
        std::cout << "file " << src_name << " opened" << std::endl;
        return;
    }

private:
    str_t src_name;
};