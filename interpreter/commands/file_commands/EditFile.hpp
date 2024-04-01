#include "../Command.hpp"

class EditFile: public Command {

public:
    EditFile() { };
    EditFile(const EditFile& other) = default;
    EditFile& operator=(const EditFile& other) = default;
    ~EditFile() = default;

    void apply(Context* context) override {
        std::cout << "file " << context->src_name << " edited" << std::endl;
        return;
    }
};