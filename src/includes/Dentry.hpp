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

    Dentry(const Dentry& other):
                d_name(other.d_name),
                d_inode(other.d_inode), 
                d_parent(other.d_parent),
                d_records_amount(other.d_records_amount),
                d_magic_numbers_map(other.d_magic_numbers_map) {}

    Dentry(Dentry&& other):
                d_name(other.d_name),
                d_inode(other.d_inode),
                d_parent(other.d_parent),
                d_records_amount(other.d_records_amount),
                d_magic_numbers_map(other.d_magic_numbers_map){
                    other.d_inode = nullptr;
                    other.d_parent = nullptr;
                    other.d_magic_numbers_map = {};
                }

    Dentry& operator=(Dentry other) {
        std::swap(d_name, other.d_name);
        std::swap(d_inode, other.d_inode);
        std::swap(d_parent, other.d_parent);
        std::swap(d_records_amount, other.d_records_amount);
        std::swap(d_magic_numbers_map, other.d_magic_numbers_map);
        return *this;
    }
    ~Dentry() { 
        if (d_parent) delete d_parent; 
        delete d_inode;
    }

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

    void d_delete_src(str_t src_name) { d_magic_numbers_map.erase(src_name); }
    void d_add_src(str_t src_name) { d_magic_numbers_map[src_name] = InodeMap::get_inode_hash(src_name); }
    bool is_src_in_directory(str_t src_name) { return d_magic_numbers_map.find(src_name) != d_magic_numbers_map.end(); }
    str_t get_d_name() { return d_name; }
    Dentry* get_parent_dir() { return d_parent; }
};