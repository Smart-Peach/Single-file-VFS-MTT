
#include "../Command.hpp"
#include "../../includes/Context.hpp"

class ReadFile: public Command {
public:
    ReadFile() { }
    ReadFile(const ReadFile& other) = default;
    ReadFile& operator=(const ReadFile& other) = default;
    ~ReadFile() = default;

    void apply(Context* context) override {
        context->get_fs()->read_file(context->get_basic_src_name());
        std::cout << "ReadFile command was applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};