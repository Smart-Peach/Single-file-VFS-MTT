#include "../includes/Superblock.hpp"

//Loads Superblock's fields into second 1024 bytes
int Superblock::load_into_memory(fstream& address_space) {

    try {
        address_space.seekg(1024);
        address_space << sizeof_fs;
        address_space << max_sizeof_file;
        address_space << sizeof_ilist_bytes;
        address_space << number_blocks;
        address_space << number_free_blocks;
        address_space << number_available_inodes;
        address_space << sizeof_block;
        address_space << free_blocks.to_string();
        address_space << endl;
        address_space.seekg(0);
    } catch (const ifstream::failure& e) {
        cout << "File is not open to load Superblock!"; 
        return 1;
    }

    return 0;
}

// Updates fields after creating new Inode
void Superblock::update_fields_after_inode_addition(Inode inode) {
    number_available_inodes--;
    number_free_blocks -= inode.get_blocks_amount();

    for (int block_address : inode.get_storage_blocks()) {
        int block_ind = (block_address - 2048 - free_blocks.size() - sizeof_ilist_bytes - size_of_rootdir) / sizeof_block;
        free_blocks.set(1);
    }

}

// Updates fields after deleting new Inode
void Superblock::update_fields_after_inode_deletion(Inode inode) {
    number_available_inodes++;
    number_free_blocks += inode.get_blocks_amount();

    for (int block_address : inode.get_storage_blocks()) {
        int block_ind = (block_address - 2048 - free_blocks.size() - sizeof_ilist_bytes - size_of_rootdir) / sizeof_block;
        free_blocks.set(0);
    }

}

//Returns address of ONE free block
int Superblock::get_free_block() {
    // TODO: USE EXISTED CHECK
    if (free_blocks.count() == free_blocks.size()) {
        cout << "Out of memory! No free blocks left!";  // TODO: throw exception
        return 2; 
    }

    int block_ind = 0;
    for (int i=0;i<free_blocks.size();i++) {
        if (free_blocks.test(i)) {
            block_ind = i;
        }
    }
    return 2048 + free_blocks.size() + sizeof_ilist_bytes + size_of_rootdir + block_ind * sizeof_block;
}

int Superblock::get_max_sizeof_file() {
    return max_sizeof_file;
}

int Superblock::get_sizeof_block() {
    return sizeof_block;
}

//Prints fields and their values to console
void Superblock::print() {
    std::cout << "Superblock:"
                << "\nfs_type: "                     << fs_type
                << "\nSizeof fs: "                   << sizeof_fs
                << "\nSizeof i-list in bytes: "      << sizeof_ilist_bytes
                << "\nSizeof root directory: "       << size_of_rootdir
                << "\nAmount of blocks: "            << number_blocks
                << "\nAmount of free blocks: "       << number_free_blocks
                << "\nAmount of available i-nodes: " << number_available_inodes
                << "\nSizeof block in bytes: "       << sizeof_block
                << "\nMax file size: "               << max_sizeof_file << endl;
    
}

// Checks whether there is a free block to store data
bool Superblock::check_free_blocks() {
    return number_free_blocks > 0;
}

// Checks whether there is a free inode
bool Superblock::check_free_inodes() {
    return number_available_inodes > 0;
}