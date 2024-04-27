
#include "../Command.hpp"
#include "../../includes/Context.hpp"

class WriteFile: public Command {
public:
    WriteFile() { }
    WriteFile(const WriteFile& other) = default;
    WriteFile& operator=(const WriteFile& other) = default;
    ~WriteFile() = default;

    void apply(Context* context) override {
        std::cout << "WriteFile command was applied to \"" << context->get_basic_src_name() << "\"\n"
                  << "Text: " << context->get_text() << std::endl;
        return;
    }
};