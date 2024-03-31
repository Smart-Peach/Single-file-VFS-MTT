#pragma once
#include <iostream>

class SuperblockException: public std::exception {
    std::string message;

public:
    SuperblockException(const std::string& message): message(message) { }
    const char* what() const noexcept override { return message.c_str(); }
};