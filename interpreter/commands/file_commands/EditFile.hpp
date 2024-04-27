
#include "../Command.hpp"
#include "../../includes/Context.hpp"

class EditFile: public Command {
public:
    EditFile() { }
    EditFile(const EditFile& other) = default;
    EditFile& operator=(const EditFile& other) = default;
    ~EditFile() = default;

    void apply(Context* context) override {
        std::cout << "EditFile command was applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};