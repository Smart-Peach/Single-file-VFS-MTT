
#include "../Command.hpp"
#include "../../includes/Context.hpp"

class AppendToFile: public Command {
public:
    AppendToFile() { }
    AppendToFile(const AppendToFile& other) = default;
    AppendToFile& operator=(const AppendToFile& other) = default;
    ~AppendToFile() = default;

    void apply(Context* context) override {
        context->get_fs()->write_to_file(context->get_basic_src_name(), context->get_text());
        std::cout << "AppendToFile command was applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};