#pragma once

#include <fstream>

#include "types.hpp" 
#include "InodeMap.hpp"
#include "Superblock.hpp"
#include "Dentry.hpp"
#include "Loader.hpp"


// Class representing our awesome filesystem
class FileSystem {
protected:
    Superblock          superblock;     // file system metadata
    InodeMap            inode_map;      // contains all inodes
    Loader*             loader; 
    Dentry*             root_dir;       // root directory
    Dentry*             current_dir;    // current directory
    std::unordered_map<str_t, Dentry*>   dentry_map;            
public:

    // FileSystem(Superblock superblock, InodeMap inode_map, Loader* loader):
    //                             superblock(superblock),
    //                             inode_map(inode_map),
    //                             loader(loader) 
    // {
    //     // init();        
    // }

    FileSystem(Loader* loader) : loader(loader) {
        std::cout << "Building file system\n";
        // loader = loader; 
        superblock = loader->unload_superblock();
        inode_map = loader->unload_inode_map(superblock.sizeof_ilist_bytes, superblock.number_blocks, 256);

        str_t root_name = "root";
        // inode_map.add_inode(1, root_name, 512);

        Dentry* root = new Dentry(root_name, inode_map.get_inode(root_name));
        root_dir = root; current_dir = root;
        dentry_map[root_name] = root;
        std::cout << "File system is built\n";
    }

    FileSystem(const FileSystem& other) = delete;
    virtual ~FileSystem() { };
    
    // Memory functions:
    // virtual void load_all_into_memory() = 0;
    // virtual void load_superblock_into_memory() = 0;
    // virtual void load_superblock_from_memory() = 0;

    // File operations:
    virtual void create_file(str_t src_name) = 0;
    virtual void delete_file(str_t src_name) = 0;
    virtual void write_to_file(str_t src_name, str_t data) = 0;
    virtual Inode& open_file(str_t src_name) = 0;
    virtual void read_file(str_t src_name) = 0;
    virtual void rename_file(str_t src_name, str_t new_name) = 0;
    virtual void close_file(str_t src_name) = 0;
    virtual void upload_to_file(str_t src_name) = 0;
    // virtual void write_to_file_with_specified_boundaries(int start, int end, str_t data, int address) = 0;

    // Directories operations:
    virtual void create_dir(str_t src_name) = 0;
    virtual void delete_dir(str_t src_name) = 0;
    virtual void add_file_to_current_dir(str_t file_name) = 0;
    virtual void delete_file_in_current_dir(str_t file_name) = 0;
    virtual Inode& open_dir(str_t src_name) = 0;
    virtual void close_dir(str_t src_name) = 0;
    virtual str_t get_working_dir_name() = 0;
    virtual void rename_dir(str_t new_name, str_t src_name) = 0;
    virtual void change_dir(str_t src_name) = 0;
    virtual void change_to_parent_dir() = 0;
    virtual bool get_existent_dir_name(str_t& src_name) = 0;
    virtual bool is_dir_empty(str_t src_name) = 0;
    virtual const std::vector<str_t> get_list_of_objects_names_in_dir(str_t src_name) = 0;
};