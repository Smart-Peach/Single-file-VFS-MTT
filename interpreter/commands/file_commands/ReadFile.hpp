
#include "../Command.hpp"
#include "../../includes/context/Context.hpp"

class ReadFile: public Command {
public:
    ReadFile(Context* ctx): Command(ctx) { }
    ReadFile(const ReadFile& other) = default;
    ReadFile& operator=(const ReadFile& other) = default;
    ~ReadFile() = default;

    void apply() override {
        std::cout << "ReadFile command applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};