#include "../Command.hpp"

class ReadDir: public Command {

public:
    ReadDir(str_t src_name): Command(src_name) { }
    ReadDir(const ReadDir& other) = default;
    ReadDir& operator=(ReadDir other){
        std::swap(src_name, other.src_name);
        return *this;
    }
    ~ReadDir() = default;

    void apply() override {
        std::cout << "directory " << src_name << " read" << std::endl;
        return;
    }

private:
    str_t src_name;
};