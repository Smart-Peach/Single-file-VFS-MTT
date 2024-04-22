
#include "../Command.hpp"
#include "../../includes/context/Context.hpp"

class OpenFile: public Command {
public:
    OpenFile(Context* ctx): Command(ctx) { }
    OpenFile(const OpenFile& other) = default;
    OpenFile& operator=(const OpenFile& other) = default;
    ~OpenFile() = default;

    void apply() override {
        std::cout << "OpenFile command applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};