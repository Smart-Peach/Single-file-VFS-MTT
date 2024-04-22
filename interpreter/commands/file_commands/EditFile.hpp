
#include "../Command.hpp"
#include "../../includes/context/Context.hpp"

class EditFile: public Command {
public:
    EditFile(Context* ctx): Command(ctx) { }
    EditFile(const EditFile& other) = default;
    EditFile& operator=(const EditFile& other) = default;
    ~EditFile() = default;

    void apply() override {
        std::cout << "EditFile command applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};