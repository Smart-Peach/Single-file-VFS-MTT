
#include "../Command.hpp"
#include "../../includes/Context.hpp"

class CreateDir: public Command {
public:
    CreateDir() { }
    CreateDir(const CreateDir& other) = default;
    CreateDir& operator=(const CreateDir& other) = default;
    ~CreateDir() = default;

    void apply(Context* context) override {
        context->get_fs()->create_dir(context->get_basic_src_name());
        std::cout << "CreateDir command was applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};