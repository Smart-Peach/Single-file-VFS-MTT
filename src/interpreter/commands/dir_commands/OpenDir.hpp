
#include "../Command.hpp"
#include "../../includes/Context.hpp"

class OpenDir: public Command {
public:
    OpenDir() { }
    OpenDir(const OpenDir& other) = default;
    OpenDir& operator=(const OpenDir& other) = default;
    ~OpenDir() = default;

    void apply(Context* context) override {
        context->get_fs()->close_dir(context->get_basic_src_name());
        std::cout << "OpenDir command was applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};