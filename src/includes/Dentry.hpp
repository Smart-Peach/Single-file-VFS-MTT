#pragma once

#include "Inode.hpp"
#include <cstddef>
#include <vector>
#include "FileSystem.hpp"


class Dentry {
    size_t        d_inode_index; // Associated with directory inode
    Dentry*       d_parent;      // Dentry object of parent
    str_t         d_name;        // Name of directory
    size_t        d_name_len;    // Length of directory's name (idk for what it's needed but let it be)
    size_t        d_records_len; // length of directory's records (len of file) 
    vector_size_t f_indexes_list; // List of files magic numbers
public:
    Dentry(size_t d_inode_index, str_t d_name, size_t d_name_len, Dentry* d_parent = nullptr):
                                                            d_inode_index(d_inode_index),
                                                            d_parent(d_parent),
                                                            d_name(d_name),
                                                            d_name_len(d_name_len),
                                                            d_records_len(0) { }

    ~Dentry() { delete d_parent; }

    // Allocates the root dentry. 
    // It is generally used in the function that is called to read
    // the superblock (fill_super), which must initialize the root directory. 
    bool d_make_root();

    // This function will be used when creating/loading
    // a new inode that does not have a dentry associated with it
    // and has not yet been introduced to the hash table of inodes
    bool d_associate_inode();

    // The lighter version of the previous call, in which the dentry 
    // was previously added in the hash table.
    bool d_create_dentry();




};