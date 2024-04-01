#include "../Command.hpp"

class DeleteFile: public Command {

public:
    DeleteFile() { };
    DeleteFile(const DeleteFile& other) = default;
    DeleteFile& operator=(const DeleteFile& other) = default;
    ~DeleteFile() = default;

    void apply(Context* context) override {
        std::cout << "file " << context->src_name << " deleted" << std::endl;
        return;
    }
};
