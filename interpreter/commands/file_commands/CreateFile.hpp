#include "../Command.hpp"

class CreateFile: public Command {

public:
    CreateFile() { };
    CreateFile(const CreateFile& other) = default;
    CreateFile& operator=(const CreateFile& other) = default;
    ~CreateFile() = default;

    void apply(Context* context) override {
        std::cout << "file " << context->src_name << " created" << std::endl;
        return;
    }
};
