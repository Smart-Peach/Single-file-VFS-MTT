#pragma once

#include "Inode.hpp"
#include <cstddef>
#include <map>


typedef std::map<str_t, size_t> d_map_t;

// The dentry is a specific part of a path that can be a directory or a file. For example, for the path /bin/vi, 
// dentry objects will be created for /, bin, and vi (a total of 3 dentry objects).

class Dentry {
    Inode*          d_inode_index;       // Associated with directory inode
    str_t           d_name;              // Name of directory
    Dentry*         d_parent;            // Dentry object of parent
    size_t          d_records_len;       // Length of directory's records (len of dir file) 
    d_map_t         d_magic_numbers_map; // Map of magic numbers of files and directories: key - name, value - magic number

public:
    Dentry(str_t d_name, Dentry* d_parent = nullptr): d_parent(d_parent),
                                                      d_name(d_name),
                                                      d_records_len(0) { }
    ~Dentry() { delete d_parent; }

    // Allocates the root dentry. 
    // It is generally used in the function that is called to read
    // the superblock (fill_super), which must initialize the root directory. 
    void d_make_root() { }

    // This function will be used when creating/loading
    // a new inode that does not have a dentry associated with it
    // and has not yet been introduced to the hash table of inodes
    void d_associate_inode() { }

    // The lighter version of the previous call, in which the dentry 
    // was previously added in the hash table.
    void d_create_dentry() { }


    void d_delete() { }
    void d_add_file() { }
    void d_add_subdir() {}

    bool is_file_in_dir(str_t src_name) {}
    bool is_subdir_in_dir(str_t src_name) {}

};