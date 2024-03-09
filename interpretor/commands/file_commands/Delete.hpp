#include "../Command.hpp"

class DeleteFile: public Command {

public:
    void apply() override {
        std::cout << "file deleted" << std::endl;
        return;
    }
};
