#include "../includes/InodeMap.hpp"
#include <cstddef>

Inode& InodeMap::operator[](int magic_number) {
    return inode_map.at(magic_number);
}

// Get nice inode hash
int InodeMap::get_inode_hash(str_t name) {
    return std::hash<str_t>{} (name);   // TODO: use our own hash func
}

Inode& InodeMap::get_inode(str_t src_name){
    // std::cout << "GET INODE " << src_name << std::endl;
    int magic_number = get_inode_hash(src_name);
    auto iter = inode_map.find(magic_number);
    if (iter == inode_map.end()) throw InodeMapException("There's no inode with name " + src_name);
    return iter->second;
};

// Add inode to InodeMap, write to FS bin file
void InodeMap::add_inode(bool src_type, str_t src_name, int address_block) {
    int magic_number = get_inode_hash(src_name);
    // std::cout << "ADD INODE " << src_name << std::endl;
    if(inode_map.find(magic_number) != inode_map.end()) {
        throw InodeMapException("Impossible to add Inode with name '" + src_name + "' because it already exists");
    }
    inode_map[magic_number] = Inode(src_type, address_block, magic_number);
};

// Special for Loader to construct InodeMap
void InodeMap::add_inode(Inode inode) {
    int magic_number = inode.get_magic_number();
    if(inode_map.find(magic_number) != inode_map.end()) {
        throw InodeMapException("Impossible to add Inode with magic number '" + std::to_string(magic_number) + "' because it already exists");
    }
    inode_map[magic_number] = inode;
};


// Delete inode from InodeMap, update FS bin file
void InodeMap::delete_inode(str_t src_name) {
    int inode_hash = get_inode_hash(src_name);
    auto iter = inode_map.find(inode_hash);
    if (iter == inode_map.end()) throw InodeMapException("Delete: There's no inode with name " + src_name);
    inode_map.erase(iter);
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
    return inode_map.find(magic_number) != inode_map.end();
};

// Pass all inodes directly to FileSystem
const inode_hashmap_t InodeMap::dump_inode_map() {
    return inode_map;
};

void InodeMap::change_magic_number_inode(str_t new_name, str_t old_name) {
    size_t new_magic_num = get_inode_hash(new_name);
    Inode& inode = get_inode(old_name);
    std::cout << "check for hash" << (get_inode_hash(old_name) == inode.get_magic_number()) << std::endl;
    auto iter = inode_map.find(inode.get_magic_number());

    if (iter == inode_map.end()) throw InodeMapException("No such source to rename!");
    inode_map.erase(iter);

    inode.change_magic_number(new_magic_num);
    if (inode.get_magic_number() != new_magic_num) std::cout << "smth went wrong1" << std::endl;
    inode_map[new_magic_num] = inode;

    if (inode_map.at(new_magic_num).get_magic_number() != new_magic_num) std::cout << "smth went wrong2" << std::endl;
    

}
