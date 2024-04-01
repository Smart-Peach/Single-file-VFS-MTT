#include "../Command.hpp"

class CloseDir: public Command {

public:
    CloseDir() { };
    CloseDir(const CloseDir& other) = default;
    CloseDir& operator=(const CloseDir& other) = default;
    ~CloseDir() = default;

    void apply(Context* context) override {
        std::cout << "directory is " << context->src_name << " closed" << std::endl;
        return;
    }
};