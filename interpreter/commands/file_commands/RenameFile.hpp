
#include "../Command.hpp"
#include "../../includes/Context.hpp"

class RenameFile: public Command {
public:
    RenameFile() { }
    RenameFile(const RenameFile& other) = default;
    RenameFile& operator=(const RenameFile& other) = default;
    ~RenameFile() = default;

    void apply(Context* context) override {
        std::cout << "RenameFile command was applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};