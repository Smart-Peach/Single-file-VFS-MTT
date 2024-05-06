
#include "../Command.hpp"
#include "../../includes/Context.hpp"

class EditFile: public Command {
public:
    EditFile() { }
    EditFile(const EditFile& other) = default;
    EditFile& operator=(const EditFile& other) = default;
    ~EditFile() = default;

    void apply(Context* context) override {
        // context->get_fs()->write_to_file_with_specified_boundaries(int start, int end, std::string data, int address);
        std::cout << "EditFile command was applied to \"" << context->get_basic_src_name() << "\"" << std::endl;
        return;
    }
};