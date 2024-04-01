#include "../Command.hpp"

class WriteFile: public Command {

public:
    WriteFile() { };
    WriteFile(const WriteFile& other) = default;
    WriteFile& operator=(const WriteFile& other) = default;
    ~WriteFile() = default;

    void apply(Context* context) override {
        std::cout << "file " << context->src_name << " written" << std::endl;
        return;
    }
};