#pragma once

#include "FileSystemException.hpp"

class IOException: virtual public FileSystemException {
    str_t message;

public:
    IOException(const str_t& message): message(message) { }
    const char* what() const noexcept override { return message.c_str(); }
};