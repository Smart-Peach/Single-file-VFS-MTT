#include "../Command.hpp"

class OpenDir: public Command {

public:
    OpenDir() { };
    OpenDir(const OpenDir& other) = default;
    OpenDir& operator=(const OpenDir& other) = default;
    ~OpenDir() = default;

    void apply(Context* context) override {
        std::cout << "file " << context->src_name << " closed" << std::endl;
        return;
    }
};