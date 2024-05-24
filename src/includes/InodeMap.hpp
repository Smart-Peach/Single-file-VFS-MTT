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
    friend Dentry;

public:
    // std::optional<Inode> get_inode(str_t src_name);
    Inode& get_inode(str_t src_name);
    void  add_inode(bool src_type, str_t src_name, int address_block);
    void  delete_inode(str_t src_name);
    void  update_inode(Inode& updated_inode);
    bool  is_file_in_directory(str_t src_name);
    
private:
    inode_hashmap_t inode_map;
    const inode_hashmap_t dump_inode_map();
    static int get_inode_hash(str_t name);
};