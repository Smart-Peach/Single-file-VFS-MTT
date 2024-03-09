#include "../Command.hpp"

class WriteFile: public Command {

public:
    void apply() override {
        std::cout << "file written" << std::endl;
        return;
    }
};