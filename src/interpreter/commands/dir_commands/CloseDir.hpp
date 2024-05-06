
#include "../Command.hpp"
#include "../../includes/Context.hpp"

class CloseDir: public Command {
public:
    CloseDir() { }
    CloseDir(const CloseDir& other) = default;
    CloseDir& operator=(const CloseDir& other) = default;
    ~CloseDir() = default;

    void apply(Context* context) override {
        std::cout << "CloseDir command was applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};