#include "../includes/Superblock.hpp"


int Superblock::get_number_of_blocks() {
    return number_blocks;
}

// //Loads Superblock's fields into second 1024 bytes
// void Superblock::load_into_memory(fstream& address_space) {

//     if (!address_space.is_open()) {
//         throw SuperblockException("Superblock: It's impossible to load, because file is closed");
//     }

//     address_space.seekg(1024);
//     address_space << sizeof_fs;
//     address_space << max_sizeof_file;
//     address_space << sizeof_ilist_bytes;
//     address_space << number_blocks;
//     address_space << number_free_blocks;
//     address_space << number_available_inodes;
//     address_space << sizeof_block;
//     address_space << size_of_rootdir;
//     address_space.seekg(2048);
//     address_space << free_blocks.to_string();
//     address_space.seekg(0);
// }

// //Reads data from second 1024 bytes and loads it to Superblock's
// void Superblock::load_from_memory(fstream& address_space) {

//     if (!address_space.is_open()) {
//         throw SuperblockException("Superblock: It's impossible to load, because file is closed");
//     }

//     address_space.seekg(1024);
//     address_space.read((char*)(&sizeof_fs), sizeof(sizeof_fs));
//     address_space.read((char*)(&max_sizeof_file), sizeof(max_sizeof_file));
//     address_space.read((char*)(&sizeof_ilist_bytes), sizeof(sizeof_ilist_bytes));
//     address_space.read((char*)(&Superblock::number_blocks), sizeof(number_blocks));
//     address_space.read((char*)(&number_free_blocks), sizeof(number_free_blocks));
//     address_space.read((char*)(&number_available_inodes), sizeof(number_available_inodes));
//     address_space.read((char*)(&sizeof_block), sizeof(sizeof_block));
//     address_space.read((char*)(&size_of_rootdir), sizeof(size_of_rootdir));
//     address_space.seekg(2048);
//     address_space.read((char*)(&free_blocks), sizeof(free_blocks));
//     address_space.seekg(0);
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

    for (int block_address : inode.get_storage_blocks()) {
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

    for (int block_address : inode.get_storage_blocks()) {
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
bool Superblock::check_num_free_blocks(int count){
    return number_free_blocks >= count;
}

int Superblock::get_max_sizeof_file() {
    return max_sizeof_file;
}

int Superblock::get_sizeof_block() {
    return sizeof_block;
}

int Superblock::get_sizeof_fs() {
    return sizeof_fs;
}

int Superblock::get_sizeof_ilist_bytes() {
    return sizeof_ilist_bytes;
}

int Superblock::get_number_of_freeblocks() {
    return number_free_blocks;
}

int Superblock::get_number_available_inodes() {
    return number_available_inodes;
}

int Superblock::get_sizeof_rootdir() {
    return size_of_rootdir;
}

bitset<Superblock::number_blocks> Superblock::get_free_blocks() {
    return free_blocks;
}
