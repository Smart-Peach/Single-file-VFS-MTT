#pragma once

#include "FileSystemException.hpp"

class InodeMapException: virtual public FileSystemException {
    str_t message;
public:
    InodeMapException(const str_t& message): message(message) { }
    const char* what() const noexcept override { return message.c_str();}
};
