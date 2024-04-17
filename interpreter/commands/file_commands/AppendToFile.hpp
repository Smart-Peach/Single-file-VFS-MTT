
#include "../Command.hpp"
#include "../../includes/context/Context.hpp"

class AppendToFile: public Command {
public:
    AppendToFile(Context* ctx): Command(ctx) { }
    AppendToFile(const AppendToFile& other) = default;
    AppendToFile& operator=(const AppendToFile& other) = default;
    ~AppendToFile() = default;

    void apply() override {
        std::cout << "AppendToFile command applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};