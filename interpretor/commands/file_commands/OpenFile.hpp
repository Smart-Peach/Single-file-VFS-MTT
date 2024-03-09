#include "../Command.hpp"

class OpenFile: public Command {

public:
    void apply() override {
        std::cout << "file opened" << std::endl;
        return;
    }
};