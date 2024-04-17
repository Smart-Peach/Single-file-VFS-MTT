
#include "../Command.hpp"
#include "../../includes/context/Context.hpp"

class RenameFile: public Command {
public:
    RenameFile(Context* ctx): Command(ctx) { }
    RenameFile(const RenameFile& other) = default;
    RenameFile& operator=(const RenameFile& other) = default;
    ~RenameFile() = default;

    void apply() override {
        std::cout << "RenameFile command applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        std::cout << '"' + context->get_basic_src_name() + "\" renamed to " + '"'+ context->get_extra_src_name() + '"' << std::endl;
        return;
    }
};