
#include "../Command.hpp"
#include "../../includes/Context.hpp"

class CloseDir: public Command {
public:
    CloseDir() { }
    CloseDir(const CloseDir& other) = default;
    CloseDir& operator=(const CloseDir& other) = default;
    ~CloseDir() = default;

    void apply(Context* context) override {
        context->get_fs()->close_dir(context->get_basic_src_name());
        std::cout << "CloseDir command was applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};