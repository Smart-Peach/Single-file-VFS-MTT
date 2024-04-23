
#include "../Command.hpp"
#include "../../includes/Context.hpp"

class AppendToFile: public Command {
public:
    AppendToFile() { }
    AppendToFile(const AppendToFile& other) = default;
    AppendToFile& operator=(const AppendToFile& other) = default;
    ~AppendToFile() = default;

    void apply(Context* context) override {
        std::cout << "AppendToFile command was applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};