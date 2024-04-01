#include "../Command.hpp"

class ReadFile: public Command {

public:
    ReadFile() { };
    ReadFile(const ReadFile& other) = default;
    ReadFile& operator=(const ReadFile& other) = default;
    ~ReadFile() = default;

    void apply(Context* context) override {
        std::cout << "file " << context->src_name << " read" << std::endl;
        return;
    }
};