#pragma once

// #include <bitset>
#include <fstream>

#include "types.hpp" 
#include "InodeMap.hpp"
#include "Superblock.hpp"

class Dentry;

// TODO: replace with real num of blocks
// static const size_t BLOCKS_AMOUNT = 10000;   
// typedef std::bitset<BLOCKS_AMOUNT> bitset_t;

// Class representing our awesome filesystem
// Considered as kind of abstraction for working with our future VFS
class FileSystem {
    friend Dentry;
protected:
    Superblock          superblock;     // file system metadata
    InodeMap            inode_map;      // contains all inodes
    std::fstream        fs_file;        // opened file

public:

    FileSystem(Superblock superblock, InodeMap inode_map, str_t fs_name):
                                superblock(superblock),
                                inode_map(inode_map) 
    {
        fs_file.open(fs_name, std::ios_base::in | std::ios_base::out | std::ios_base::binary);
        
    }
    FileSystem(const FileSystem& other) = delete;
    virtual ~FileSystem() { };

    // Memory functions:
    virtual void load_all_into_memory() = 0;
    virtual void load_superblock_into_memory() = 0;
    virtual void load_superblock_from_memory() = 0;

    // File operations:
    virtual void create_file(str_t src_name) = 0;
    virtual void delete_file(str_t src_name) = 0;
    virtual void write_to_file(str_t src_name, str_t data) = 0;
    virtual Inode& open_file(str_t src_name) = 0;
    virtual void read_file(str_t src_name) = 0;
    virtual void close_file(str_t src_name) = 0;
    virtual void upload_to_file(str_t src_name) = 0;
    virtual void write_to_file_with_specified_boundaries(int start, int end, str_t data, int address) = 0;
    virtual void update_inode(Inode& inode, int size, int new_address) = 0;

    // Directories operations:
    
    virtual void create_dir(str_t src_name) = 0;
    virtual void delete_dir(str_t src_name) = 0;
    virtual void add_file_to_dir(str_t file_name, str_t dir_name) = 0;
    virtual void delete_file_in_dir(str_t file_name, str_t dir_name) = 0;
    virtual Inode open_dir(str_t src_name) = 0;
    virtual void close_dir(str_t src_name) = 0;
    virtual void link_dir(str_t src_name) = 0;
    virtual void unlink_dir(str_t src_name) = 0;
};