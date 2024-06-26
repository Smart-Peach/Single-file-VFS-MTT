#pragma once

#include <iostream>
#include "../includes/types.hpp"

class InterpreterException: public std::exception {
    str_t message;

public:
    InterpreterException(const str_t& message): message(message) { }
    const char* what() const noexcept override { return message.c_str(); }
};
