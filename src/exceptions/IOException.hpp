#pragma once
#include <iostream>

class IOException: public std::exception {
    std::string message;

public:
    IOException(const std::string& message): message(message) { }
    const char* what() const noexcept override { return message.c_str(); }
};