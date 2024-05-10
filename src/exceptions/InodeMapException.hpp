#pragma once
#include <iostream>
#include "../includes/types.hpp"

class InodeMapException: public std::exception {
    str_t message;

public:
    InodeMapException(const str_t& message): message(message) { }
    const char* what() const noexcept override { return message.c_str();}
};
