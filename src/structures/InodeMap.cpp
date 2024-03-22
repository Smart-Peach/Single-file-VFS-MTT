#include "InodeMap.hpp"

Inode InodeMap::get_inode(str_t src_name){
    std::cout << "inode of \"" << src_name << "\" source is being observed";
};
void  InodeMap::add_inode(str_t src_name) {};
void  InodeMap::delete_inode(str_t src_name) {};
void  InodeMap::update_inode(str_t src_name) {};

bool  InodeMap::is_file_in_directory(str_t src_name) {};
void  InodeMap::load_inode_to_memory(Inode inode) {};
void  InodeMap::load_inode_to_memory(str_t inode) {};
void  InodeMap::dump_inode_map() {};