#include "../Command.hpp"

class UnlinkDir: public Command {

public:
    UnlinkDir() { };
    UnlinkDir(const UnlinkDir& other) = default;
    UnlinkDir& operator=(const UnlinkDir& other) = default;
    ~UnlinkDir() = default;

    void apply(Context* context) override {
        std::cout << "file " << context->src_name << " closed" << std::endl;
        return;
    }
};