
#include "../Command.hpp"
#include "../../includes/Context.hpp"

class DeleteDir: public Command {
public:
    DeleteDir() { }
    DeleteDir(const DeleteDir& other) = default;
    DeleteDir& operator=(const DeleteDir& other) = default;
    ~DeleteDir() = default;

    void apply(Context* context) override {
        std::cout << "DeleteDir command was applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};