#pragma once
#include <iostream>
#include "../includes/types.hpp"

class SuperblockException: public std::exception {
    str_t message;

public:
    SuperblockException(const str_t& message): message(message) { }
    const char* what() const noexcept override { return message.c_str(); }
};