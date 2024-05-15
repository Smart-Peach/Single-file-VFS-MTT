
#include "../Command.hpp"
#include "../../includes/Context.hpp"

class MoveFile: public Command {
public:
    MoveFile() { }
    MoveFile(const MoveFile& other) = default;
    MoveFile& operator=(const MoveFile& other) = default;
    ~MoveFile() = default;

    void apply(Context* context) override {
        // TODO: implement dir commands and call them
        context->get_fs()->delete_file(context->get_basic_src_name());
        context->get_fs()->create_file(context->get_extra_src_name(), context->get_mode());
        std::cout << "MoveFile command was applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};