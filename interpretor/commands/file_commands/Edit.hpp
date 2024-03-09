#include "../Command.hpp"

class EditFile: public Command {

public:
    void apply() override {
        std::cout << "file edited" << std::endl;
        return;
    }
};