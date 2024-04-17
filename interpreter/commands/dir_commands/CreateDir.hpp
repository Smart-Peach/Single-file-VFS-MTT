
#include "../Command.hpp"
#include "../../includes/context/Context.hpp"

class CreateDir: public Command {
public:
    CreateDir(Context* ctx): Command(ctx) { }
    CreateDir(const CreateDir& other) = default;
    CreateDir& operator=(const CreateDir& other) = default;
    ~CreateDir() = default;

    void apply() override {
        std::cout << "CreateDir command applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};