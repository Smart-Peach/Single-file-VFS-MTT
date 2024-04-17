
#include "../Command.hpp"
#include "../../includes/context/Context.hpp"

class SeekFile: public Command {
public:
    SeekFile(Context* ctx): Command(ctx) { }
    SeekFile(const SeekFile& other) = default;
    SeekFile& operator=(const SeekFile& other) = default;
    ~SeekFile() = default;

    void apply() override {
        std::cout << "SeekFile command applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};