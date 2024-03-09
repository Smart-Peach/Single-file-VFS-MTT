#include "../Command.hpp"

class SeekFile: public Command {

public:
    void apply() override {
        std::cout << "file sought" << std::endl;
        return;
    }
};