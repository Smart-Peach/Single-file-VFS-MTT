#include <iostream>

class Superblock {
// Contains information about file system in general

private:
    const std::string fs_type                 = "linear";   // Maybe special structure should be here (aka fs_type)
    const int         sizeof_fs               = 1073741824; // Sizeof file system in bytes, 1 Gb
    const int         max_sizeof_file         = 104857600;  // Maximum available file size, 1 Mb
    int               sizeof_ilist_bytes      = 214726656;  // Sizeof ilist in bytes (in memory) 
    int               number_free_blocks      = 838776;     // Number of blocks available for data storage
    int               number_available_inodes = 838776;     // Number of inodes available for storage
    const int         sizeof_block            = 1024;       // Sizeof one block
    int*              free_blocks;                          // Bit table????


public:

    void load_into_memory() {
        //Loads Superblock's fields into second 1024 bytes
        
    }

    int get_free_block() {
        //Returns address of ONE free block
        return 0;
    }

    int get_max_sizeof_file() {
        return Superblock::max_sizeof_file;
    }

    int get_sizeof_block() {
        return Superblock::sizeof_block;
    }

    void print() {
        //Prints fields and their values to console
    
    }

    bool check_free_blocks() {
        // Checks whether there is a free block to store data
        return Superblock::number_free_blocks > 0;
    }

    bool check_free_inodes() {
        // Checks whether there is a free inode
        return Superblock::number_available_inodes > 0;
    }

};
