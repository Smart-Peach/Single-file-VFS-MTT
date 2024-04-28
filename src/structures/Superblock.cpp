#include "../includes/Superblock.hpp"


// int Superblock::get_number_of_blocks() {
//     return number_blocks;
// }

// Updates fields after creating new Inode
void Superblock::update_fields_after_inode_addition(Inode inode) {
    if (!Superblock::check_free_blocks()) {
        throw SuperblockException("Superblock: no free inodes left! Addition of inode was failed.");
    }

    if (!Superblock::check_free_blocks()){
        throw SuperblockException("Superblock: no free blocks left! Addition of Inode was failed.");
    }

    number_available_inodes--;
    number_free_blocks -= inode.get_blocks_amount();

    for (int block_address : inode.get_blocks_storage()) {
        int block_ind = (block_address - 2048 - free_blocks.size() - sizeof_ilist_bytes - size_of_rootdir) / sizeof_block;
        if (free_blocks.test(block_ind)) {
            throw SuperblockException("Superblock: block with index " + std::to_string(block_ind) + " and actual address " + std::to_string(block_address) + " is already busy! Adding an Inode was failed!");
        }
        free_blocks.set(1);
    }

}

// Updates fields after deleting new Inode
void Superblock::update_fields_after_inode_deletion(Inode inode) {
    number_available_inodes++;
    number_free_blocks += inode.get_blocks_amount();

    for (int block_address : inode.get_blocks_storage()) {
        int block_ind = (block_address - 2048 - free_blocks.size() - sizeof_ilist_bytes - size_of_rootdir) / sizeof_block;
        free_blocks[block_ind] = 0;
    }

}

//Returns address of ONE free block
int Superblock::get_free_block() {
    if (!check_free_blocks()) {
        throw SuperblockException("Superblock: no free blocks left!");
    }

    int block_ind = 0;
    for (int i=0;i<free_blocks.size();i++) {
        if (free_blocks.test(i)) {
            block_ind = i;
        }
    }

    int block_address = 1024 + 1024 + free_blocks.size() + sizeof_ilist_bytes + size_of_rootdir + block_ind * sizeof_block;

    if (block_address + sizeof_block >= sizeof_fs) {
        throw SuperblockException("Superblock: CORE DUMPED! Block is beyond file system boundaries!");
    }

    return block_address; 
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

//Checks whether there are the required number of free blocks. 
bool Superblock::check_needed_number_of_free_blocks(int count){
    return number_free_blocks >= count;
}