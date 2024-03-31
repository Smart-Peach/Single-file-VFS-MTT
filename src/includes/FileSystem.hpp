#pragma once

#include <bitset>
#include <fstream>
#include "InodeMap.hpp"
#include "Superblock.hpp"

// TODO: replace with real num of blocks
static const size_t BLOCKS_AMOUNT = 10000;      
typedef std::bitset<BLOCKS_AMOUNT> bitset_t;

// Class representing our awesome filesystem
// Considered as kind of abstraction for working with our future VFS
class FileSystem {

private:
    Superblock          superblock;     // file system metadata
    bitset_t            free_blocks;    // TODO: naming - not only free blocks
    InodeMap            inode_map;      // contains all inodes
    std::fstream        fs_file;        // opened file
public:
    virtual ~FileSystem() = 0;
    virtual void write_to_file(string, string) = 0;
    virtual void open_file(string) = 0;
    virtual void read_file(string) = 0;
    virtual void close_file(string) = 0;
    virtual void upload_to_file(string) = 0;
};