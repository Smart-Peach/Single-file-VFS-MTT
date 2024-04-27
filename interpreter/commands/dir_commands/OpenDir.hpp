
#include "../Command.hpp"
#include "../../includes/Context.hpp"

class OpenDir: public Command {
public:
    OpenDir() { }
    OpenDir(const OpenDir& other) = default;
    OpenDir& operator=(const OpenDir& other) = default;
    ~OpenDir() = default;

    void apply(Context* context) override {
        std::cout << "OpenDir command was applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};