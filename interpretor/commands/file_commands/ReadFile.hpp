#include "../Command.hpp"

class ReadFile: public Command {

public:
    ReadFile(str_t src_name): Command(src_name) { }
    ReadFile(const ReadFile& other) = default;
    ReadFile& operator=(ReadFile other){
        std::swap(src_name, other.src_name);
        return *this;
    }
    ~ReadFile() = default;

    void apply() override {
        std::cout << "file " << src_name << " read" << std::endl;
        return;
    }

private:
    str_t src_name;
};