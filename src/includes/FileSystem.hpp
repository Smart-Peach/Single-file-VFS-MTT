#pragma once

// #include <bitset>
#include <fstream>

#include "types.hpp" 
#include "InodeMap.hpp"
#include "Superblock.hpp"
#include "Dentry.hpp"
//#include "Loader.hpp"


// Class representing our awesome filesystem
class FileSystem {
protected:
    Superblock                           superblock;     // file system metadata
    InodeMap                             inode_map;      // contains all inodes
    std::fstream                         fs_file;        // opened file
    const Dentry*                        root_dir;       // root directory
    Dentry*                              current_dir;    // current directory
    std::unordered_map<str_t, Dentry*>   dentry_map;     // stores an abs path for dentries. Key - path, Val - dentry
    // Loader*             loader;             

public:

    // TODO: add initialization for root and curent directories
    FileSystem(Superblock superblock, InodeMap inode_map, str_t fs_name, Dentry* root_dir):
                                root_dir(root_dir),
                                current_dir(root_dir),
                                superblock(superblock),
                                inode_map(inode_map)
    {   
        dentry_map[root_dir->d_name] = root_dir;
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

    // Directories operations:
    virtual void create_dir(str_t src_name) = 0;
    virtual void delete_dir(str_t src_name) = 0;
    virtual void add_file_to_dir(str_t file_name, str_t dir_name) = 0;
    virtual void delete_file_in_dir(str_t file_name, str_t dir_name) = 0;
    virtual Inode& open_dir(str_t src_name) = 0;
    virtual void close_dir(str_t src_name) = 0;
    // virtual void link_dir(str_t src_name) = 0;
    // virtual void unlink_dir(str_t src_name) = 0;
    virtual void change_dir(str_t src_name) = 0;
};