
#include "../Command.hpp"
#include "../../includes/Context.hpp"

class CreateFile: public Command {
public:
    CreateFile() { }
    CreateFile(const CreateFile& other) = default;
    CreateFile& operator=(const CreateFile& other) = default;
    ~CreateFile() = default;

    void apply(Context* context) override {
        context->get_fs()->create_file(context->get_basic_src_name());
        std::cout << "CreateFile command was applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};