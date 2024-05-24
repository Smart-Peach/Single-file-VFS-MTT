#pragma once

#include <fstream>

#include "types.hpp" 
#include "InodeMap.hpp"
#include "Superblock.hpp"


// Abstract class which helps to work with address space. It loads to memory our structures 
// and provides functions for reading from address space 
class Loader {
private:
    virtual char read_char(size_t address) = 0;
    virtual unsigned int  read_int(size_t address) = 0;
    virtual const char* read_constchar(size_t address) = 0;

    virtual void write_char(size_t address, char ch) = 0;
    virtual void write_int(size_t address, unsigned int num) = 0;
    virtual void write_constchar(size_t address, const char* string) = 0;

public: 
    virtual void load_superblock(Superblock superblock) = 0;
    virtual void load_inode_map() = 0;
    virtual void load_rootdir() = 0;

    virtual Superblock unload_superblock() = 0;
    virtual void unload_inode_map() = 0;
    virtual void unload_rootdir() = 0;
};
