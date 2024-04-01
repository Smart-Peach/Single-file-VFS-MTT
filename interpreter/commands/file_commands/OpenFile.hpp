#include "../Command.hpp"

class OpenFile: public Command {

public:
    OpenFile() { };
    OpenFile(const OpenFile& other) = default;
    OpenFile& operator=(const OpenFile& other) = default;
    ~OpenFile() = default;

    void apply(Context* context) override {
        std::cout << "file " << context->src_name << " opened" << std::endl;
        return;
    }
};