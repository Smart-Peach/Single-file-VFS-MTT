#include <iostream>

class Inode {
// describes exact file or directory

private:

    int         magic_number;          // Unique number of inode (aka hash) 
    int         optional_bit1 = 0;     // | bits for permissions (optional)
    int         optional_bit2 = 0;     // |
    int         number_references;     // Number of references to file
    std::string identifier;            // Identificator of owner/user and group-owner (Maybe another type)
    int         sizeof_file;           // Current sizeof file
    int         last_access_time;      // | Maybe another type
    int         last_file_modif_time;  // |
    int         last_inode_modif_time; // | 
    int         amount_blocks;         // Сurrent sizeof the array with storage block addresses
    int         storage_blocks[];      // Array of storage block addresses


public:

    int* get_storage_blocks() {  // Maybe another type
        return storage_blocks;
    }

    void print() { //Print all fields of inode 
        std::cout << "Magic number of inode = " << magic_number << std::endl;
        std::cout << "optional_bit1 = " << optional_bit1 << std::endl;
        std::cout << "optional_bit2 = " << optional_bit2 << std::endl;
        std::cout << "Number of references to file = " << number_references << std::endl;
        std::cout << "Identificator of owner/user and group-owner = " << identifier << std::endl;
        std::cout << "Current sizeof file = " << sizeof_file << std::endl;
        std::cout << "Time of the last access to the file = " << last_access_time << std::endl;
        std::cout << "Time of the last file modification = " << last_file_modif_time << std::endl;
        std::cout << "Time of the last inode modification = " << last_inode_modif_time << std::endl;
        std::cout << "Current sizeof array with storage block addresses = " << amount_blocks << std::endl;
        std::cout << "Array of storage block addresses: ";
        for(int i = 0; i < amount_blocks; i++) std::cout << storage_blocks[i] << " ";
    }

// hz whether we need this:
    int get_sizeof_file() {
        return sizeof_file;
    }

    void set_magic_number(int new_magic_number){
        magic_number = new_magic_number;
    }

    int get_magic_number() {
        return magic_number;
    }
    
};