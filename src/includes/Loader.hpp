#pragma once

#include <fstream>

#include "types.hpp" 
#include "InodeMap.hpp"
#include "Superblock.hpp"


// Abstract class which helps to work with address space. It loads to memory our structures 
// and provides functions for reading from address space 
class Loader {
private:
    virtual unsigned int  read_int(size_t& address) = 0;
    virtual str_t read_string(size_t& address) = 0;

    virtual void write_int(size_t& address, unsigned int num) = 0;
    virtual void write_string(size_t& address, const str_t string) = 0;

public:
    Loader() = default;
    Loader(const Loader& other) = delete;
    virtual ~Loader() {};

    virtual char read_char(size_t& address) = 0;
    virtual void write_char(size_t& address, char ch) = 0;
    virtual void write_string_with_limits(size_t& address, int start, int num_of_char, str_t data) = 0;

    virtual void load_superblock(Superblock superblock) = 0;
    virtual void load_inode_map(InodeMap& mapa, size_t sizeof_freeblocks, size_t sizeof_inode) = 0;
    virtual void load_rootdir() = 0;

    virtual Superblock unload_superblock() = 0;
    virtual InodeMap unload_inode_map(size_t sizeof_ilist, size_t sizeof_freeblocks, size_t sizeof_inode) = 0;
    virtual void unload_rootdir() = 0;
};
