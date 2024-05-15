#pragma once

#include <fstream>
#include <bitset>
#include "../includes/Inode.hpp"
#include "../exceptions/SuperblockException.hpp"
#include "types.hpp"


// Contains information about file system in general
class Superblock {
// TODO: add field for root directory
    const char*           fs_type                 = "linear";   // Maybe special structure should be here (aka fs_type)
    const int             sizeof_fs               = 1073741824; // Sizeof file system in bytes, 1 Gb
    const int             max_sizeof_file         = 104857600;  // Maximum available file size, 1 Mb
    int                   sizeof_ilist_bytes      = 214726656;  // Sizeof ilist in bytes (in memory) 
    static const int      number_blocks           = 800000;     // Number of all blocks (occupied and free)
    int                   number_free_blocks      = 800000;     // Number of blocks available for data storage
    int                   number_available_inodes = 800000;     // Number of inodes available for storage
    const int             sizeof_block            = 1024;       // Sizeof one block
    const int             size_of_rootdir         = 512;        // Size of root directory
    std::bitset<number_blocks> free_blocks;                          // May be faster in case array of bool --> in beginning 838776 0's 

    int get_block_address_by_bit_ind(int bit_ind);
    int get_block_bit_ind_by_address(int block_address);

public:

    // Superblock(const char* fs_type, int sizeof_fs, int max_sizeof_file, int sizeof_ilist_bytes, int number_blocks, int number_free_blocks, int number_available_inodes, int sizeof_block, int size_of_rootdir )
    // : fs_type(fs_type),
    //   sizeof_fs(sizeof_fs),
    //   max_sizeof_file(max_sizeof_file),
    //   sizeof_ilist_bytes(sizeof_ilist_bytes),
    //   number_blocks(number_blocks),
    //   number_free_blocks(number_free_blocks),
    //   number_available_inodes(number_available_inodes),
    //   sizeof_block(sizeof_block),
    //   size_of_rootdir(size_of_rootdir) {}

    //Loads Superblock's fields into second 1024 bytes
    void load_into_memory(std::fstream& address_space);
    void load_from_memory(std::fstream& address_space);
    void update_fields_after_inode_addition(Inode& inode);
    void update_fields_after_inode_deletion(Inode& inode);

    // int get_number_of_blocks();

    //Returns address of ONE free block
    int get_free_block();
    void print();
    bool check_free_blocks();
    bool check_free_inodes();
    bool check_needed_number_of_free_blocks(int count);

    friend class AwesomeFileSystem;
    friend class TestSuperblock;
    friend class LoaderBinFile;
};