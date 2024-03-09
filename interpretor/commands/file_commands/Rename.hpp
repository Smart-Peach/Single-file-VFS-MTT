#include "../Command.hpp"

class RenameFile: public Command {

public:
    void apply() override {
        std::cout << "file renamed" << std::endl;
        return;
    }
};