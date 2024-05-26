
#include "../Command.hpp"
#include "../../includes/Context.hpp"

class ChangeDir: public Command {
public:
    ChangeDir() { }
    ChangeDir(const ChangeDir& other) = default;
    ChangeDir& operator=(const ChangeDir& other) = default;
    ~ChangeDir() = default;

    void apply(Context* context) override {
        std::cout << "ChangeDir command was applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};