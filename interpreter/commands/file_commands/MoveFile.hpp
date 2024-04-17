
#include "../Command.hpp"
#include "../../includes/context/Context.hpp"

class MoveFile: public Command {
public:
    MoveFile(Context* ctx): Command(ctx) { }
    MoveFile(const MoveFile& other) = default;
    MoveFile& operator=(const MoveFile& other) = default;
    ~MoveFile() = default;

    void apply() override {
        std::cout << "MoveFile command applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        std::cout << '"' + context->get_basic_src_name() + "\" moved to " + '"'+ context->get_extra_src_name() + '"' << std::endl;
        return;
    }
};