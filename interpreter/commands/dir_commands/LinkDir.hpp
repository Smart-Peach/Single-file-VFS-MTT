
#include "../Command.hpp"
#include "../../includes/Context.hpp"

class LinkDir: public Command {
public:
    LinkDir() { }
    LinkDir(const LinkDir& other) = default;
    LinkDir& operator=(const LinkDir& other) = default;
    ~LinkDir() = default;

    void apply(Context* context) override {
        std::cout << "LinkDir command was applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};