
#include "../Command.hpp"
#include "../../includes/context/Context.hpp"

class WriteFile: public Command {
public:
    WriteFile(Context* ctx): Command(ctx) { }
    WriteFile(const WriteFile& other) = default;
    WriteFile& operator=(const WriteFile& other) = default;
    ~WriteFile() = default;

    void apply() override {
        std::cout << "WriteFile command applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        std::cout << "Input text: " << context->get_text() << std::endl;
        return;
    }
};