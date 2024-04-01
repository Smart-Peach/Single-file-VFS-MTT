#include "../Command.hpp"

class SeekFile: public Command {

public:
    SeekFile() { };
    SeekFile(const SeekFile& other) = default;
    SeekFile& operator=(const SeekFile& other) = default;
    ~SeekFile() = default;

    void apply(Context* context) override {
        std::cout << "file " << context->src_name << " seeked" << std::endl;
        return;
    }
};