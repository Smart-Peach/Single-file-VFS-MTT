#include "../Command.hpp"

class SeekFile: public Command {

public:
    SeekFile() = default;
    SeekFile(str file_name):
        file_name(file_name) {};
    ~SeekFile() {};
    
    void apply() override {
        std::cout << "file " << file_name << " sought" << std::endl;
        return;
    }

private:
    str file_name;
};