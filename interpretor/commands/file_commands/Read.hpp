#include "../Command.hpp"

class ReadFile: public Command {

public:
    void apply() override {
        std::cout << "file read" << std::endl;
        return;
    }
};