#include "../Command.hpp"

class CreateDir: public Command {

public:
    CreateDir() { };
    CreateDir(const CreateDir& other) = default;
    CreateDir& operator=(const CreateDir& other) = default;
    ~CreateDir() = default;

    void apply(Context* context) override {
        std::cout << "file " << context->src_name << " closed" << std::endl;
        return;
    }
};