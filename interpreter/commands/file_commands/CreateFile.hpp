
#include "../Command.hpp"
#include "../../includes/context/Context.hpp"

class CreateFile: public Command {
public:
    CreateFile(Context* ctx): Command(ctx) { }
    CreateFile(const CreateFile& other) = default;
    CreateFile& operator=(const CreateFile& other) = default;
    ~CreateFile() = default;

    void apply() override {
        std::cout << "CreateFile command applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};