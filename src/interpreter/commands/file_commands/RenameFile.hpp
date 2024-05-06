
#include "../Command.hpp"
#include "../../includes/Context.hpp"

class RenameFile: public Command {
public:
    RenameFile() { }
    RenameFile(const RenameFile& other) = default;
    RenameFile& operator=(const RenameFile& other) = default;
    ~RenameFile() = default;

    void apply(Context* context) override {
        Inode inode = context->get_fs()->open_file(context->get_basic_src_name());
        Inode new_inode(0);
        std::cout << "RenameFile command was applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};