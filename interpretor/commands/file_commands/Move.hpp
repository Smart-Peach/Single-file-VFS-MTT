#include "../Command.hpp"

class MoveFile: public Command {

public:
    void apply() override {
        std::cout << "file moved" << std::endl;
        return;
    }
};