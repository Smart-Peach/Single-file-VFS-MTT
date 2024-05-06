
#include "../Command.hpp"
#include "../../includes/Context.hpp"

class UnlinkDir: public Command {
public:
    UnlinkDir() { }
    UnlinkDir(const UnlinkDir& other) = default;
    UnlinkDir& operator=(const UnlinkDir& other) = default;
    ~UnlinkDir() = default;

    void apply(Context* context) override {
        std::cout << "UnlinkDir command was applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};