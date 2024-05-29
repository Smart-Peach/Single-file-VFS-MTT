
#include "../Command.hpp"
#include "../../includes/Context.hpp"

class ChangeDir: public Command {
public:
    ChangeDir() { }
    ChangeDir(const ChangeDir& other) = default;
    ChangeDir& operator=(const ChangeDir& other) = default;
    ~ChangeDir() = default;

    void apply(Context* context) override {
        if (context->get_basic_src_name() == "..") context->get_fs()->change_to_parent_dir();
        else context->get_fs()->change_dir(context->get_basic_src_name());
        std::cout << "ChangeDir command was applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};