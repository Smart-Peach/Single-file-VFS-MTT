
#include "../Command.hpp"
#include "../../includes/context/Context.hpp"

class LinkDir: public Command {
public:
    LinkDir(Context* ctx): Command(ctx) { }
    LinkDir(const LinkDir& other) = default;
    LinkDir& operator=(const LinkDir& other) = default;
    ~LinkDir() = default;

    void apply() override {
        std::cout << "LinkDir command applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};