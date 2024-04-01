#include "../Command.hpp"

class RenameDir: public Command {

public:
    RenameDir() { };
    RenameDir(const RenameDir& other) = default;
    RenameDir& operator=(const RenameDir& other) = default;
    ~RenameDir() = default;

    void apply(Context* context) override {
        std::cout << "file " << context->src_name << " closed" << std::endl;
        return;
    }
};