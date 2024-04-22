
#include "../Command.hpp"
#include "../../includes/context/Context.hpp"

class CloseDir: public Command {
public:
    CloseDir(Context* ctx): Command(ctx) { }
    CloseDir(const CloseDir& other) = default;
    CloseDir& operator=(const CloseDir& other) = default;
    ~CloseDir() = default;

    void apply() override {
        std::cout << "CloseDir command applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};