#include "../Command.hpp"

class ReadDir: public Command {

public:
    ReadDir() { };
    ReadDir(const ReadDir& other) = default;
    ReadDir& operator=(const ReadDir& other) = default;
    ~ReadDir() = default;

    void apply(Context* context) override {
        std::cout << "file " << context->src_name << " closed" << std::endl;
        return;
    }
};