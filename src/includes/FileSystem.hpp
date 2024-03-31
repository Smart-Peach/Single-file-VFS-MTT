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

protected:
    Superblock          superblock;     // file system metadata
    bitset_t            free_blocks;    // TODO: naming - not only free blocks
    InodeMap            inode_map;      // contains all inodes
    std::fstream        fs_file;        // opened file

public:

    FileSystem(Superblock superblock, bitset_t free_blocks, InodeMap inode_map, str_t fs_name):
                                superblock(superblock),
                                free_blocks(free_blocks), 
                                inode_map(inode_map) 
    {
        fs_file.open(fs_name, std::ios_base::out | std::ios_base::binary);
        fs_file.close();
    };
    FileSystem(const FileSystem& other) = delete;
    virtual ~FileSystem() = 0;

    virtual void write_to_file(string, string) = 0;
    virtual void open_file(string) = 0;
    virtual void read_file(string) = 0;
    virtual void close_file(string) = 0;
    virtual void upload_to_file(string) = 0;
};