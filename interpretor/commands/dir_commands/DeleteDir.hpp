#include "../Command.hpp"

class DeleteDir: public Command {

public:
    DeleteDir(str_t dir_name):
        dir_name(dir_name) {};
    DeleteDir(const DeleteDir& other) = default;
    DeleteDir& operator=(DeleteDir other){
        std::swap(dir_name, other.dir_name);
        return *this;
    }
    ~DeleteDir() = default;

    void apply() override {
        std::cout << "directory " << dir_name << " deleted" << std::endl;
        return;
    }

private:
    str_t dir_name;
};