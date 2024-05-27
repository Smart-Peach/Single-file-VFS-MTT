#pragma once

#include "FileSystemException.hpp"

class SuperblockException: virtual public FileSystemException {
    str_t message;

public:
    SuperblockException(const str_t& message): message(message) { }
    const char* what() const noexcept override { return message.c_str(); }
};