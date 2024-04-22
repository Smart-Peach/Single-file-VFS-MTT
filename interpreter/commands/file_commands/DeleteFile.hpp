
#include "../Command.hpp"
#include "../../includes/context/Context.hpp"

class DeleteFile: public Command {
public:
    DeleteFile(Context* ctx): Command(ctx) { }
    DeleteFile(const DeleteFile& other) = default;
    DeleteFile& operator=(const DeleteFile& other) = default;
    ~DeleteFile() = default;

    void apply() override {
        std::cout << "DeleteFile command applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};