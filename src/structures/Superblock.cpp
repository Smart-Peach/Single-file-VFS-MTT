#include "../includes/Superblock.hpp"

//Loads Superblock's fields into second 1024 bytes
int Superblock::load_into_memory(FILE* address_space) { 

    // TODO: check sizeof(address_space) == 1024
    try {
        fseek(address_space, 3, SEEK_SET);
        fputs(fs_type, address_space);
        fprintf(address_space, "%d", sizeof_fs);

        // out << sizeof_fs;
        // out << max_sizeof_file;
        // out << sizeof_ilist_bytes;
        // out << number_blocks;
        // out << number_free_blocks;
        // out << number_available_inodes;
        // out << sizeof_block;
        // out << free_blocks.to_string();  // may be error
    } catch (const ifstream::failure& e) {
        cout << "File is not open to load Superblock!"; 
        return 1;
    }

    return 0;
}

//Returns address of ONE free block
int Superblock::get_free_block() {
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

void Superblock::print() {
    //Prints fields and their values to console
    std::cout << "Superblock:"
                << "\nfs_type: "                     << fs_type
                << "\nSizeof fs: "                   << sizeof_fs
                << "\nSizeof i-list in bytes: "      << sizeof_ilist_bytes
                << "\nSizeof root directory: "       << size_of_rootdir
                << "\nAmount of blocks: "            << number_blocks
                << "\nAmount of free blocks: "       << number_free_blocks
                << "\nAmount of available i-nodes: " << number_available_inodes
                << "\nSizeof block in bytes: "       << sizeof_block
                << "\nMax file size: "               << max_sizeof_file;
    
}

bool Superblock::check_free_blocks() {
    // Checks whether there is a free block to store data
    return number_free_blocks > 0;
}

bool Superblock::check_free_inodes() {
    // Checks whether there is a free inode
    return number_available_inodes > 0;
}