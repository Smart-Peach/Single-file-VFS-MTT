#pragma once

#include <iostream>
#include <unordered_map>
#include "Inode.hpp"
#include "../exceptions/InodeMapException.hpp"
#include "types.hpp"

// Key   - magic_number (name hash)
// Value - instance of Inode
typedef std::unordered_map<size_t, Inode> inode_hashmap_t;


/*
* Class for containing file inode instances.
* Implemented via unordered_map (aka hash map).
*/

class Dentry;
class InodeMap {
    friend class Dentry;
    friend class FileSystem;

public:
    Inode& operator[](int magic_number);
    // std::optional<Inode> get_inode(str_t src_name);
    Inode& get_inode(str_t src_name);
    void  add_inode(bool src_type, str_t src_name, int address_block);
    void  add_inode(Inode inode);
    void  delete_inode(str_t src_name);
    void  update_inode(Inode& updated_inode);
    bool  is_file_in_directory(str_t src_name);
    void change_magic_number_inode(str_t new_name,  str_t old_name);
    
private:
    inode_hashmap_t inode_map;
    const inode_hashmap_t dump_inode_map();
    static int get_inode_hash(str_t name);

    friend class LoaderBinFile;
    friend class LoaderTest;
};