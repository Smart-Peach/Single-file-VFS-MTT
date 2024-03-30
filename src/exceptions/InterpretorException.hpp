#pragma once

#include <iostream>

class InterpretorException: public std::exception {
    std::string message;

public:
    InterpretorException(const std::string& message): message(message) { }
    const char* what() const noexcept override { return message.c_str(); }
};
