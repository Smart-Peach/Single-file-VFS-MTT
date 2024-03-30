#include "../Command.hpp"

class DeleteDir: public Command {

public:
    DeleteDir(str_t src_name): Command(src_name) { }
    DeleteDir(const DeleteDir& other) = default;
    DeleteDir& operator=(DeleteDir other){
        std::swap(src_name, other.src_name);
        return *this;
    }
    ~DeleteDir() = default;

    void apply() override {
        std::cout << "directory " << src_name << " deleted" << std::endl;
        return;
    }

private:
    str_t src_name;
};