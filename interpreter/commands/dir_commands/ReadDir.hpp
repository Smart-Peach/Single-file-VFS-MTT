
#include "../Command.hpp"
#include "../../includes/context/Context.hpp"

class ReadDir: public Command {
public:
    ReadDir(Context* ctx): Command(ctx) { }
    ReadDir(const ReadDir& other) = default;
    ReadDir& operator=(const ReadDir& other) = default;
    ~ReadDir() = default;

    void apply() override {
        std::cout << "ReadDir command applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};