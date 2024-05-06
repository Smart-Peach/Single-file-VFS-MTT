
#include "../Command.hpp"
#include "../../includes/Context.hpp"

class DeleteFile: public Command {
public:
    DeleteFile() { }
    DeleteFile(const DeleteFile& other) = default;
    DeleteFile& operator=(const DeleteFile& other) = default;
    ~DeleteFile() = default;

    void apply(Context* context) override {
        context->get_fs()->delete_file(context->get_basic_src_name());
        std::cout << "DeleteFile command was applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};