#pragma once

#include <iostream>

class InterpreterException: public std::exception {
    std::string message;

public:
    InterpreterException(const std::string& message): message(message) { }
    const char* what() const noexcept override { return message.c_str(); }
};
