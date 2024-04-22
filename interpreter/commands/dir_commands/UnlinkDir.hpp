
#include "../Command.hpp"
#include "../../includes/context/Context.hpp"

class UnlinkDir: public Command {
public:
    UnlinkDir(Context* ctx): Command(ctx) { }
    UnlinkDir(const UnlinkDir& other) = default;
    UnlinkDir& operator=(const UnlinkDir& other) = default;
    ~UnlinkDir() = default;

    void apply() override {
        std::cout << "UnlinkDir command applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};