#pragma once

#include <iostream>
#include <unordered_map>
#include "Inode.hpp"


typedef std::unordered_map<size_t, Inode> inode_hashmap_t;
typedef std::string str_t;


/**
* @brief Class for containing file inode instances.
* @brief Implemented via unordered_map (aka hash map).
*/
class InodeMap {

public:
    Inode get_inode(str_t src_name);
    void  add_inode(str_t src_name);
    void  delete_inode(str_t src_name);
    void  update_inode(str_t src_name);
    bool  is_file_in_directory(str_t src_name);
    
private:
    inode_hashmap_t inode_map;
    void  dump_inode_map();
    void  load_inode_to_memory(Inode inode);
    void  load_inode_to_memory(str_t inode);
};