#pragma once

#include "FileSystemException.hpp"

class OutOfMemoryException: virtual public FileSystemException {
    str_t message;

public:
    OutOfMemoryException(const str_t& message): message(message) { }
    const char* what() const noexcept override { return message.c_str(); }
};