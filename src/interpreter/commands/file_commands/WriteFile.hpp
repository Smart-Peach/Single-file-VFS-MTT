
#include "../Command.hpp"
#include "../../includes/Context.hpp"

class WriteFile: public Command {
public:
    WriteFile() { }
    WriteFile(const WriteFile& other) = default;
    WriteFile& operator=(const WriteFile& other) = default;
    ~WriteFile() = default;

    void apply(Context* context) override {
        context->get_fs()->write_to_file(context->get_basic_src_name(), context->get_text());
        std::cout << "WriteFile command was applied to \"" << context->get_basic_src_name() << "\"\n"
                  << "Text: " << context->get_text() << std::endl;
        return;
    }
};