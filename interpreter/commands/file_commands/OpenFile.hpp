
#include "../Command.hpp"
#include "../../includes/Context.hpp"

class OpenFile: public Command {
public:
    OpenFile() { }
    OpenFile(const OpenFile& other) = default;
    OpenFile& operator=(const OpenFile& other) = default;
    ~OpenFile() = default;

    void apply(Context* context) override {
        context->get_fs()->open_file(context->get_basic_src_name());
        std::cout << "OpenFile command was applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};