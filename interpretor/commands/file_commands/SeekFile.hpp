#include "../Command.hpp"

class SeekFile: public Command {

public:
    SeekFile() = default;
    SeekFile(str_t file_name):
        file_name(file_name) {};
    ~SeekFile() {};
    
    void apply() override {
        std::cout << "file " << file_name << " sought" << std::endl;
        return;
    }

private:
    str_t file_name;
};