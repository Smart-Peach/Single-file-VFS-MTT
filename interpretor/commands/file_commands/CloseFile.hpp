#include "../Command.hpp"

class CloseFile: public Command {

public:
    void apply() override {
        std::cout << "file closed" << std::endl;
        return;
    }
};