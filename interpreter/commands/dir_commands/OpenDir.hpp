
#include "../Command.hpp"
#include "../../includes/context/Context.hpp"

class OpenDir: public Command {
public:
    OpenDir(Context* ctx): Command(ctx) { }
    OpenDir(const OpenDir& other) = default;
    OpenDir& operator=(const OpenDir& other) = default;
    ~OpenDir() = default;

    void apply() override {
        std::cout << "OpenDir command applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};