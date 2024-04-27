
#include "../Command.hpp"
#include "../../includes/Context.hpp"

class ReadDir: public Command {
public:
    ReadDir() { }
    ReadDir(const ReadDir& other) = default;
    ReadDir& operator=(const ReadDir& other) = default;
    ~ReadDir() = default;

    void apply(Context* context) override {
        std::cout << "ReadDir command was applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};