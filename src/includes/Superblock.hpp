#pragma once

#include <iostream>
#include <fstream>
#include <bitset>
#include "../includes/Inode.hpp"
#include "../exceptions/SuperblockException.hpp"
#include "../includes/AwesomeFileSystem.hpp"

using namespace std;

// Contains information about file system in general
class Superblock {

private:
// TODO: move to header constatnts 
    const char*           fs_type                 = "linear";   // Maybe special structure should be here (aka fs_type)
    const int             sizeof_fs               = 1073741824; // Sizeof file system in bytes, 1 Gb
    const int             max_sizeof_file         = 104857600;  // Maximum available file size, 1 Mb
    int                   sizeof_ilist_bytes      = 214726656;  // Sizeof ilist in bytes (in memory) 
    static const int      number_blocks           = 800000;     // Number of all blocks (occupied and free)
    int                   number_free_blocks      = 800000;     // Number of blocks available for data storage
    int                   number_available_inodes = 800000;     // Number of inodes available for storage
    const int             sizeof_block            = 1024;       // Sizeof one block
    const int             size_of_rootdir         = 512;        // Size of root directory
    bitset<number_blocks> free_blocks;                          // May be faster in case array of bool --> in beginning 838776 0's 


public:

    //Loads Superblock's fields into second 1024 bytes
    void load_into_memory(fstream& address_space);
    void load_from_memory(fstream& address_space);
    void update_fields_after_inode_addition(Inode inode);
    void update_fields_after_inode_deletion(Inode inode);

    int get_number_of_blocks();

    //Returns address of ONE free block
    int get_free_block();
    int get_max_sizeof_file();
    int get_sizeof_block();
    int get_sizeof_fs();
    int get_sizeof_ilist_bytes();
    int get_number_of_freeblocks();
    int get_number_available_inodes();
    int get_sizeof_rootdir();
    bitset<Superblock::number_blocks> get_free_blocks();
    void print();
    bool check_free_blocks();
    bool check_free_inodes();

    friend void FileSystem::load_superblock_into_memory();
};