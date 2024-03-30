#include "../Command.hpp"

class SeekFile: public Command {

public:
    SeekFile(str_t src_name): Command(src_name) { }
    SeekFile(const SeekFile& other) = default;
    SeekFile& operator=(SeekFile other){
        std::swap(src_name, other.src_name);
        return *this;
    }
    ~SeekFile() = default;
    
    void apply() override {
        std::cout << "file " << src_name << " sought" << std::endl;
        return;
    }

};