#include "../includes/InodeMap.hpp"

// Get nice inode hash
int InodeMap::get_inode_hash(str_t name) {
    return std::hash<str_t>{} (name);   // TODO: use our own hash func
}

Inode& InodeMap::get_inode(str_t src_name){
    try {
        int magic_number = get_inode_hash(src_name);
        return inode_map.at(magic_number);      
    } catch (std::out_of_range) { throw InodeMapException("There's no inode with name " + src_name); }
};

// Add inode to InodeMap, write to FS bin file
void InodeMap::add_inode(bool src_type, str_t src_name) {
    int magic_number = get_inode_hash(src_name);
    if(inode_map.find(magic_number) != inode_map.end()) {
        throw InodeMapException("Impossible to add Inode with name '" + src_name + "' because it already exists");
    }
    inode_map[magic_number] = Inode(src_type);
};

void InodeMap::add_inode(bool src_type, str_t src_name, int address_block) {
    int magic_number = get_inode_hash(src_name);
    if(inode_map.find(magic_number) != inode_map.end()) {
        throw InodeMapException("Impossible to add Inode with name '" + src_name + "' because it already exists");
    }
    inode_map[magic_number] = Inode(src_type, address_block);
};

// Delete inode from InodeMap, update FS bin file
void InodeMap::delete_inode(str_t src_name) {
    int inode_hash = get_inode_hash(src_name);
    inode_map.erase(inode_hash);
};

// Update inode in InodeMap and in FS bin file
void InodeMap::update_inode(Inode& updated_inode) {
    int inode_hash = updated_inode.get_magic_number();
    if(inode_map.find(inode_hash) == inode_map.end()) {
        throw InodeMapException("Impossible to update Inode with hash '" + std::to_string(inode_hash) + "' because it doesn't exist");
    }
    inode_map[inode_hash] = updated_inode;
};

// Check whether file is in directory 
bool InodeMap::is_file_in_directory(str_t src_name) {
    int magic_number = get_inode_hash(src_name);
    // TODO: fix  
    // if (get_inode(src_name)) return false;
    return true;
};

// Pass all inodes directly to FileSystem
const inode_hashmap_t InodeMap::dump_inode_map() {
    return inode_map;
};


