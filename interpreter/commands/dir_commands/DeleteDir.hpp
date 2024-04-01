#include "../Command.hpp"

class DeleteDir: public Command {

public:
    DeleteDir() { };
    DeleteDir(const DeleteDir& other) = default;
    DeleteDir& operator=(const DeleteDir& other) = default;
    ~DeleteDir() = default;

    void apply(Context* context) override {
        std::cout << "file " << context->src_name << " closed" << std::endl;
        return;
    }
};