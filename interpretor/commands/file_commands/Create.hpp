#include "../Command.hpp"

class CreateFile: public Command {

public:
    void apply() override {
        std::cout << "file created" << std::endl;
        return;
    }
};
