
#include "../Command.hpp"
#include "../../includes/Context.hpp"

class SeekFile: public Command {
public:
    SeekFile() { }
    SeekFile(const SeekFile& other) = default;
    SeekFile& operator=(const SeekFile& other) = default;
    ~SeekFile() = default;

    void apply(Context* context) override {
        std::cout << "SeekFile command was applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};