#include "../Command.hpp"

class DeleteFile: public Command {

public:
    DeleteFile() = default;
    DeleteFile(str file_name):
        file_name(file_name) {};
    ~DeleteFile() {};

    void apply() override {
        std::cout << "file " << file_name << " deleted" << std::endl;
        return;
    }

private:
    str file_name;
};
