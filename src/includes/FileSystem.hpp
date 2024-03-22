#pragma once

#include <bitset>
#include <fstream>
#include "InodeMap.hpp"
#include "../structures/Superblock.cpp"

// TODO: replace with real num of blocks
static const size_t BLOCKS_AMOUNT = 10000;      
typedef std::bitset<BLOCKS_AMOUNT> bitset_t;

// Class represanting our awesome filesystem
// Considered as kind of abstraction for working with our future VFS
class FileSystem {

private:
    Superblock          superblock;     // file system metadata
    bitset_t            free_blocks;    // TODO: naming - not only free blocks
    InodeMap            inode_map;      // contains all inodes
    std::fstream        fs_file;        // opened file

public: 
    // TODO: should it take name of the file to open or (mb) already opened file?
    FileSystem(Superblock superblock, bitset_t free_blocks, 
                        InodeMap inode_map, str_t fs_name):
                                    superblock(superblock),
                                    free_blocks(free_blocks), 
                                    inode_map(inode_map) 
        {
            fs_file.open(fs_name, std::ios_base::out | std::ios_base::binary);
            fs_file.close();
        }
};