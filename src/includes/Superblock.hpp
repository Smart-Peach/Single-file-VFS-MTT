#include <iostream>
#include <fstream>
#include <bitset>
#include <cstdio>
#include <string>

using namespace std;

class Superblock {
// Contains information about file system in general

private:
// TODO: move to header constatnts 
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
    int load_into_memory(FILE* address_space);
    //Returns address of ONE free block
    int get_free_block();
    int get_max_sizeof_file();
    int get_sizeof_block();
    void print();
    bool check_free_blocks();
    bool check_free_inodes();

};