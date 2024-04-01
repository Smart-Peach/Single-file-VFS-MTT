#include "../Command.hpp"

class LinkDir: public Command {

public:
    LinkDir() { };
    LinkDir(const LinkDir& other) = default;
    LinkDir& operator=(const LinkDir& other) = default;
    ~LinkDir() = default;

    void apply(Context* context) override {
        std::cout << "file " << context->src_name << " closed" << std::endl;
        return;
    }
};