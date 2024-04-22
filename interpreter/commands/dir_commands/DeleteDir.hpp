
#include "../Command.hpp"
#include "../../includes/context/Context.hpp"

class DeleteDir: public Command {
public:
    DeleteDir(Context* ctx): Command(ctx) { }
    DeleteDir(const DeleteDir& other) = default;
    DeleteDir& operator=(const DeleteDir& other) = default;
    ~DeleteDir() = default;

    void apply() override {
        std::cout << "DeleteDir command applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};