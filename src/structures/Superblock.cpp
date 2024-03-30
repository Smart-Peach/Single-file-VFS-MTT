#include <iostream>
#include <fstream>
#include <bitset>
#include <cstdio>
#include <string>

using namespace std;

class Superblock {
// Contains information about file system in general

private:
// TODO: move constants to header 
    const char*           fs_type                 = "linear";   // Maybe special structure should be here (aka fs_type)
    const int             sizeof_fs               = 1073741824; // Sizeof file system in bytes, 1 Gb
    const int             max_sizeof_file         = 104857600;  // Maximum available file size, 1 Mb
    int                   sizeof_ilist_bytes      = 214726656;  // Sizeof ilist in bytes (in memory) 
    static const int      number_blocks           = 838776;     // Number of all blocks (occupied and free)
    int                   number_free_blocks      = 838776;     // Number of blocks available for data storage
    int                   number_available_inodes = 838776;     // Number of inodes available for storage
    const int             sizeof_block            = 1024;       // Sizeof one block
    const int             size_of_rootdir         = 512;        // Size of root directory
    bitset<number_blocks> free_blocks;                          // May be faster in case array of bool --> in beginning 838776 0's 


public:

    //Loads Superblock's fields into second 1024 bytes
    int load_into_memory(FILE* address_space) { 

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
    int get_free_block() {
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

    int get_max_sizeof_file() {
        return Superblock::max_sizeof_file;
    }

    int get_sizeof_block() {
        return Superblock::sizeof_block;
    }

    void print() {
        //Prints fields and their values to console
        std::cout << "Superblock:"
                  << "\nfs_type: "                     << Superblock::fs_type
                  << "\nSizeof fs: "                   << Superblock::sizeof_fs
                  << "\nSizeof i-list in bytes: "      << Superblock::sizeof_ilist_bytes
                  << "\nSizeof root directory: "       << Superblock::size_of_rootdir
                  << "\nAmount of blocks: "            << Superblock::number_blocks
                  << "\nAmount of free blocks: "       << Superblock::number_free_blocks
                  << "\nAmount of available i-nodes: " << Superblock::number_available_inodes
                  << "\nSizeof block in bytes: "       << Superblock::sizeof_block
                  << "\nMax file size: "               << Superblock::max_sizeof_file;
        
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
