#include "../Command.hpp"

class MoveFile: public Command {

public:
    MoveFile() { };
    MoveFile(const MoveFile& other) = default;
    MoveFile& operator=(const MoveFile& other) = default;
    ~MoveFile() = default;

    void apply(Context* context) override {
        std::cout << "file " << context->src_name << " moved" << std::endl;
        return;
    }
};