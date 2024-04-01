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
    // bitset_t            free_blocks;    // TODO: naming - not only free blocks
    InodeMap            inode_map;      // contains all inodes
    std::fstream        fs_file;        // opened file

public:

    FileSystem(Superblock superblock, InodeMap inode_map, str_t fs_name):
                                superblock(superblock),
                                inode_map(inode_map) 
    {
        fs_file.open(fs_name, std::ios_base::out | std::ios_base::binary);
        
    }
    FileSystem(const FileSystem& other) = delete;
    virtual ~FileSystem() { };

    // virtual void load_all_into_memory() = 0;
    // virtual void load_superblock_into_memory() =0;
    virtual void write_to_file(string src_name, string data) = 0;
    virtual void open_file(string src_name) = 0;
    virtual void read_file(string src_name) = 0;
    virtual void close_file(string src_name) = 0;
    virtual void upload_to_file(string src_name) = 0;
};