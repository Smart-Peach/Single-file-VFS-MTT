#include "../Command.hpp"

class WriteFile: public Command {

public:
    WriteFile(str_t src_name): Command(src_name) { }
    WriteFile(const WriteFile& other) = default;
    WriteFile& operator=(WriteFile other){
        std::swap(src_name, other.src_name);
        return *this;
    }
    ~WriteFile() = default;

    void apply() override {
        std::cout << "file " << src_name << " written" << std::endl;
        return;
    }

    void apply(FileSystem* fs) override {
        fs->write_to_file(src_name, "Hello world");
        return;
    }

};