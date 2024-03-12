#include "../Command.hpp"

class SeekFile: public Command {

public:
    SeekFile(str_t file_name):
        file_name(file_name) {};
    SeekFile(const SeekFile& other) = default;
    SeekFile& operator=(SeekFile other){
        std::swap(file_name, other.file_name);
        return *this;
    }
    ~SeekFile() = default;
    
    void apply() override {
        std::cout << "file " << file_name << " sought" << std::endl;
        return;
    }

private:
    str_t file_name;
};