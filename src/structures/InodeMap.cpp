#include "../includes/InodeMap.hpp"


// Get inode from InodeMap by the file name
Inode InodeMap::get_inode(str_t src_name){
    std::cout << "inode of \"" << src_name << "\" source is being observed";
};

// Create file inode
// Add it to InodeMap, write to FS bin file
void  InodeMap::add_inode(str_t src_name) {};

// Delete file inode
// Delete it from InodeMap, update FS bin file
void  InodeMap::delete_inode(str_t src_name) {};

// Update file inode:
// Update inode in InodeMap and in FS bin file
void  InodeMap::update_inode(str_t src_name) {};

// Check whether file is in directory 
bool  InodeMap::is_file_in_directory(str_t src_name) {};

// Load inode directly into FS bin file (Inode instance)
void  InodeMap::load_inode_to_memory(Inode inode) {};

// Load inode directly into FS bin file (search in InodeMap by the file name)
void  InodeMap::load_inode_to_memory(str_t inode) {};

// Load all inodes directly into FS bin file
void  InodeMap::dump_inode_map() {};