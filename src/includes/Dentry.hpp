#pragma once

#include "Inode.hpp"
#include "InodeMap.hpp"

#include <cstddef>
#include <map>


typedef std::map<str_t, size_t> d_map_t;

// The dentry is a specific part of a path that can be a directory or a file. For example, for the path /bin/vi, 
// dentry objects will be created for /, bin, and vi (a total of 3 dentry objects).

class Dentry {
    friend class FileSystem;
    Inode*          d_inode;             // associated inode
    str_t           d_name;              // Name of directory
    Dentry*         d_parent;            // Dentry object of parent
    size_t          d_records_amount;    // amount of records in binary file (for Loader)
    d_map_t         d_magic_numbers_map; // Map of magic numbers of files and directories: key - name, value - magic number

public:
    Dentry(str_t d_name, Inode* inode, Dentry* d_parent = nullptr, size_t records_amount = 0, d_map_t d_map = {}):
                                                                    d_parent(d_parent),
                                                                    d_name(d_name),
                                                                    d_inode(inode),
                                                                    d_records_amount(records_amount),
                                                                    d_magic_numbers_map(d_map) { }
    ~Dentry() { delete d_parent; }

    // // Allocates the root dentry. 
    // // It is generally used in the function that is called to read
    // // the superblock (fill_super), which must initialize the root directory. 
    // void d_make_root() { }

    // // This function will be used when creating/loading
    // // a new inode that does not have a dentry associated with it
    // // and has not yet been introduced to the hash table of inodes

    // void d_associate_inode() { }
    // // The lighter version of the previous call, in which the dentry 
    // // was previously added in the hash table.

    void d_delete_src(str_t src_name) { }
    void d_add_file(str_t src_name) {
        d_magic_numbers_map[src_name] = InodeMap::get_inode_hash(src_name);
    }

    void d_add_dir(str_t src_name) {
        d_magic_numbers_map[src_name] = InodeMap::get_inode_hash(src_name);
    }

    str_t get_d_name() { return d_name; }

    bool is_file_in_directory(str_t src_name) {}
    bool is_subdir_in_directory(str_t src_name) {}

};