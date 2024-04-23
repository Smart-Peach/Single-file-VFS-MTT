
#include "../Command.hpp"
#include "../../includes/Context.hpp"

class CloseFile: public Command {
public:
    CloseFile() { }
    CloseFile(const CloseFile& other) = default;
    CloseFile& operator=(const CloseFile& other) = default;
    ~CloseFile() = default;

    void apply(Context* context) override {
        std::cout << "CloseFile command was applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};