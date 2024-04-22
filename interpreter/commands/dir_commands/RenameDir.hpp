
#include "../Command.hpp"
#include "../../includes/context/Context.hpp"

class RenameDir: public Command {
public:
    RenameDir(Context* ctx): Command(ctx) { }
    RenameDir(const RenameDir& other) = default;
    RenameDir& operator=(const RenameDir& other) = default;
    ~RenameDir() = default;

    void apply() override {
        std::cout << "RenameDir command applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        std::cout << '"' + context->get_basic_src_name() + "\" renamed to " + '"'+ context->get_extra_src_name() + '"' << std::endl;
        return;
    }
};