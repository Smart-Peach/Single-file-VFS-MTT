#include "../Command.hpp"

class CloseFile: public Command {

public:
    CloseFile() { };
    CloseFile(const CloseFile& other) = default;
    CloseFile& operator=(const CloseFile& other) = default;
    ~CloseFile() = default;

    void apply(Context* context) override {
        std::cout << "file " << context->src_name << " closed" << std::endl;
        return;
    }
};