
#include "../Command.hpp"
#include "../../includes/Context.hpp"

class RenameDir: public Command {
public:
    RenameDir() { }
    RenameDir(const RenameDir& other) = default;
    RenameDir& operator=(const RenameDir& other) = default;
    ~RenameDir() = default;

    void apply(Context* context) override {
        context->get_fs()->rename_dir(context->get_basic_src_name(), context->get_extra_src_name());
        std::cout << "RenameDir command was applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};