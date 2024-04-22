
#include "../Command.hpp"
#include "../../includes/context/Context.hpp"

class CloseFile: public Command {
public:
    CloseFile(Context* ctx): Command(ctx) { }
    CloseFile(const CloseFile& other) = default;
    CloseFile& operator=(const CloseFile& other) = default;
    ~CloseFile() = default;

    void apply() override {
        std::cout << "CloseFile command applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};