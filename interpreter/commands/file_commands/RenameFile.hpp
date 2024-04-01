#include "../Command.hpp"

class RenameFile: public Command {

public:
    RenameFile() { };
    RenameFile(const RenameFile& other) = default;
    RenameFile& operator=(const RenameFile& other) = default;
    ~RenameFile() = default;

    void apply(Context* context) override {
        std::cout << "file " << context->src_name << " renamed" << std::endl;
        return;
    }
};