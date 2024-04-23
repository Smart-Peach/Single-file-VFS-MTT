
#include "../Command.hpp"
#include "../../includes/Context.hpp"

class MoveFile: public Command {
public:
    MoveFile() { }
    MoveFile(const MoveFile& other) = default;
    MoveFile& operator=(const MoveFile& other) = default;
    ~MoveFile() = default;

    void apply(Context* context) override {
        std::cout << "MoveFile command was applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};